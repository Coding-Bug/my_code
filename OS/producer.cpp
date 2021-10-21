#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define BUFFER_SIZE 100 // 缓冲区数量
#define MAX_SEQ     200 // 
#define N_CONSUMER  10  // 消费者数量
#define N_PRODUCER  10  // 生产者数量
#define T_CONSUME   100000  // 消费者休息时间(毫秒)
#define T_PRODUCE   100000  // 生产者休息时间
#define OVER ( -1 )   // 停止标志

#define FULL(ALOOP)(ALOOP.nused == BUFFER_SIZE)
#define EMPTY(ALOOP)(ALOOP.nused == 0)
#define NEXT(P)(((P+1)==(BUFFER_SIZE))?0:(P-1))
#define PREV(P)(((P)==0)?(BUFFER_SIZE-1):(P-1))
#define AFTERW_EMPTONOEMP(ALOOP)(ALOOP.nused == 1)
#define AFTERR_FULLTONOFULL(ALOOP)(ALOOP.nused == BUFFER_SIZE-1)

struct ArrayLoop
{
   int buffer[BUFFER_SIZE];
   int readpos,writepos; // 读写指针，指向将要读写的weizhi
   unsigned int nused;   // 已经使用过的数量
};
int seq = 0;

typedef struct prodcons{
   // 缓冲区相关数据结构
   struct ArrayLoop aloop;
   pthread_mutex_t lock;   // 互斥体lock 用于对缓冲区的互斥访问
   pthread_cond_t notempty; // 缓冲区非空的条件变量
   pthread_cond_t notfull;  // 缓冲区未满的条件变量
}Prodcons;

Prodcons g_prod;

// 初始化缓冲区结构
void init (Prodcons *b){
   pthread_mutex_init(&b->lock,NULL); // 创建互斥锁
   pthread_cond_init(&b->notempty,NULL);  
   pthread_cond_init(&b->notfull,NULL);
   b->aloop.readpos = 0;
   b->aloop.writepos = 0;
   b->aloop.nused = 0;
}

void cleanup_handler(void* arg){
   pthread_mutex_unlock(&g_prod.lock);
}

// 将铲平放入缓冲区，这里是存入一个整数当作产品
int put(Prodcons *b,unsigned int pid){
    pthread_mutex_lock(&b->lock);
    // 等待缓冲区未满
    while(FULL(b->aloop)){
       printf("\033[1;35m p[%d]: write full,wait notfull\n",pid);
       pthread_cond_wait(&b->notfull,&b->lock);
    }
    int data  = seq;
    if(data == MAX_SEQ){
       pthread_mutex_unlock(&b->lock);
       return 1;
    }

    // 写数据，并移动指针
    b->aloop.buffer[b->aloop.writepos]=data;
    printf("\033[1;35m p[%d] put the pos %d,data %d\n",pid,b->aloop.writepos,data); 
    ++b->aloop.nused;
    b->aloop.writepos = NEXT(b->aloop.writepos);


    // 设置缓冲区非空的条件变量
    if(AFTERW_EMPTONOEMP(b->aloop)){
        printf("\330[1;35m p[%d] : nodata=>havedata signal\n",pid);
        pthread_cond_broadcast(&b->notempty);
    }

    ++seq;
    pthread_mutex_unlock(&b->lock);
    return 0;
}

// 从缓冲区中取出整数
int get(Prodcons*b,int pid){
   int data;
   pthread_mutex_lock(&b->lock);

   // 等待缓冲区非空
   while(EMPTY(b->aloop)){
      printf("\003[1;35m c[%d] : read empty, wait data\n",pid);
      pthread_cond_wait(&b->notempty,&b->lock);
   }
   // 读数据，移动读指针
   data = b->aloop.buffer[b->aloop.readpos];
   if(OVER == data){
      pthread_mutex_unlock(&b->lock);
      return data;
   }

   printf("\003[1;32m c[%d] get pos %d,,product %d\n",pid,b->aloop.readpos,data);
   --b->aloop.nused;
   b->aloop.readpos = NEXT(b->aloop.readpos); // 读指针移动

   // 设置缓冲区未满的条件变量
   if(AFTERR_FULLTONOFULL(b->aloop)){
      printf("\033[1:35m c[%d] : full=>notfull signal\n",pid);
      pthread_cond_broadcast(&b->notfull);
   }
   pthread_mutex_unlock(&b->lock);
   return data;
}

//  生产者线程
void *producer(void *data){
   unsigned int thn = *(unsigned int*)data;
   printf("p[%d]\n",thn);
   pthread_cleanup_push(cleanup_handler,NULL);
   
   while(1){
      usleep(T_PRODUCE);
      if(1 == put(&g_prod,thn)){
         break;
      }
   }
   printf("p[%d] producer stop\n",thn);
   
   return NULL;
   pthread_cleanup_pop(0);  
}

void *consumer(void *data){
   int thn = *(int*) data;
   printf("c[%d]\n",thn);
   pthread_cleanup_push(cleanup_handler,NULL);

   int d;
   while(1){
      usleep(T_CONSUME);
      d=get(&g_prod,thn);
      if(d == OVER){
         break;
      }
   }

   printf("c[%d] consumer stop\n",thn);

   return NULL;
   pthread_cleanup_pop(0);
}


// 主函数
int main(){
   pthread_t th_p[N_PRODUCER];
   pthread_t th_c[N_CONSUMER];
   void *retval;
   init(&g_prod);
   int i;

   pthread_setconcurrency(N_PRODUCER+N_CONSUMER);

   // 创建生产则会和消费者线程
   for(int i = 0;i<N_PRODUCER;++i){
      pthread_create(&th_p[i],NULL,producer,(unsigned int*)&th_c[i]);
   }
   for(int i = 0;i<N_CONSUMER;++i){
      pthread_create(&th_c[i],NULL,consumer,(int*)&th_c[i]);  
   }


   // 两个线程结束
   for(int i = 0;i<N_PRODUCER;++i){
      pthread_join(th_p[i],&retval);
   }
   printf("here readpos[%d],writepos[%d],seq[%d]\n",g_prod.aloop.readpos,g_prod.aloop.writepos,seq);

   g_prod.aloop.buffer[g_prod.aloop.writepos]=OVER;
   ++g_prod.aloop.nused;
   pthread_cond_broadcast(&g_prod.notempty);
   for(int i = 0;i<N_PRODUCER;++i){
      pthread_join(th_c[i],&retval);
   }
   printf("\033[1;100m\n");
   return 0;
}
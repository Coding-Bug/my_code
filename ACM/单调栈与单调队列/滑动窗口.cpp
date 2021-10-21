#include<iostream>
using namespace std;
#define maxn 1000005
int n,k;
long long a[maxn];
int q[maxn];       // 单调队列
int head=0;
int tail=0;
void findmin(){
    head=tail=0;   // 清空队列
    for(int i = 1;i<k;++i){     // k个前的入队，即，还差一个形成窗口
       // 入队之前看看能不能干掉一些不可能的
       while(head>tail&&a[q[head-1]]>a[i]){  // 从队头出去，因为是从小到大，所以队头的大，队头先出
           head--;
       }
       q[head++]=i;     // 当前结点入队
    }
    for(int i=k;i<=n;++i){
        // 入队之前同样检查队列中后进来的是不是比当前大
        // 如果大，则出队，他们不会是最小了，
        while(head>tail&&a[q[head-1]]>a[i]){
            head--;
        }
        q[head++]=i;
        // 很久之前入队的已经不属于这个窗口了，出队
        // 如果这个队尾足够小，他可以输出k次
        while(head>tail&&(i-q[tail]+1)>k){
            tail++;
        }
        // 现在这个窗口的队尾是最小值了，至少现在是，以后是不是不一定
        // 以后被挤掉也没事，他已经当过属于他的最小值了
        cout<<a[q[tail]]<<" ";
    }
    cout<<endl; 
}

void findmax(){
    head=tail=0;   // 清空队列
    for(int i = 1;i<k;++i){     // k个前的入队，即，还差一个形成窗口
       // 入队之前看看能不能干掉一些不可能的
       while(head>tail&&a[q[head-1]]<a[i]){  // 从队头出去，因为是从小到大，所以队头的大，队头先出
           head--;
       }
       q[head++]=i;     // 当前结点入队
    }
    for(int i=k;i<=n;++i){
        // 入队之前同样检查队列中后进来的是不是比当前大
        // 如果大，则出队，他们不会是最小了，
        while(head>tail&&a[q[head-1]]<a[i]){
            head--;
        }
        q[head++]=i;
        // 很久之前入队的已经不属于这个窗口了，出队
        // 如果这个队尾足够小，他可以输出k次
        while(head>tail&&(i-q[tail]+1)>k){
            tail++;
        }
        // 现在这个窗口的队尾是最小值了，至少现在是，以后是不是不一定
        // 以后被挤掉也没事，他已经当过属于他的最小值了
        cout<<a[q[tail]]<<" ";
    }
    cout<<endl; 
}


int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    for(int i = 1;i<=n;++i){
        cin>>a[i];
    }
    findmin();
    findmax();

}
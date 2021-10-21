#include<bits/stdc++.h>
using namespace std;

bool canV[5][5];  // 访问过或者是墙都不能访问
typedef struct POINT{
    int x;
    int y;
}POINT;
typedef struct NODE{
    POINT root[25];  //存放路径，路径中最后一个结点则是当前节点
    int n;  // 路径中现有点的个数,也就是路径长度
}NODE;
int Mov[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//移动

int maze[5][5]; //迷宫
NODE ans;  // 答案结点



// bfs求解最短路径
void bfs(){
    queue<NODE> Q;
    // 初始化第一个结点
    NODE p;
    p.n=1;
    p.root[0].x=0;
    p.root[0].y=0;
    canV[0][0]=false;

    // 第一个结点入队
    Q.push(p);

    // 搜索最短路径
    while(!Q.empty()){
      // 取出队头 
      p=Q.front();
      Q.pop();

      // 定义还未拓展的叶子结点
      NODE q;
      q.n=p.n+1;
      for(int i = 0;i<p.n;++i){
          q.root[i]=p.root[i];
      }
     
      int nx,ny;  // 移动后的坐标
      // 分别向四个不同方向位移
      for(int e=0;e<4;e++){
         nx=p.root[p.n-1].x+Mov[e][0];
         ny=p.root[p.n-1].y+Mov[e][1];
         if(nx<0||ny<0||nx>4||ny>4){
             continue;
         }
         // 若该结点能访问,则给q赋值
         if(canV[nx][ny]){
            q.root[q.n-1].x=nx;
            q.root[q.n-1].y=ny;
         }else{
             continue;
         }
         // 如果移动后的点为终点
         if(nx==4&&ny==4){
            // 判断是否为下届
            if(q.n==9){
               ans=q;
               return;
            }
            // 判断是否比已经求出的可能答案小
            // 若小，则更新
            if(q.n<ans.n){
                ans.n=q.n;
                for(int i = 0;i<q.n;++i){
                  ans.root[i]=q.root[i];
                }
            }
            continue;
         }
         
         // 若为普通结点，则进队
         //cout<<q.root[q.n-1].x<<"   "<<q.root[q.n-1].y<<endl;
         Q.push(q);
         canV[nx][ny]=false;    
        }
      
    }

}

int main()
{
    //freopen("test/Labyrinth.txt","r",stdin);
    // 初始化答案的解为最大值
    ans.n=0x7fffffff;
    // 初始化标记数组
    for(int i = 0;i<5;++i){
        for(int j = 0;j<5;++j){
            canV[i][j]=true;
        }
    }
    
    for(int i = 0;i<5;++i){
        for(int j=0;j<5;++j){
            cin>>maze[i][j];
            if(maze[i][j]==1){
                canV[i][j]=false;
            }
        }
    }
    bfs();
    
    //输出结果
    for(int i = 0;i<ans.n;++i){
        printf("(%d,%d)\n",ans.root[i].x,ans.root[i].y);
    }
    return 0;


}
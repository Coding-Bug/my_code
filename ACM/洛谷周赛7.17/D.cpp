#include<iostream>
#include<queue>
using namespace std;
typedef struct Node{
    int x,y;     // 当前结点的位置
    int step=0;  // 当前的转角数
}Node;
bool visit[103][103];  // 某个点是否已经访问过，即已经入队
int Move[4][2]={{0,1},{0,-1},{-1,0},{1,0}};   // 移动
int W;
int H;
char str[103][103];
int BX;
int BY; // 开始结点
void bfs(){
     queue<Node> Q;
     Node p;
     p.x=BX;
     p.y=BY;
     Q.push(p);
     while(!Q.empty()){
         p=Q.front();
         Q.pop();
         int lx=p.x;
         int ly=p.y;
         int step=p.step;
         for(int e=0;e<4;++e){
             int nx=lx+Move[e][0];
             int ny=ly+Move[e][1];
             // 沿着一条线一直走，直到撞墙
             while(nx<W&&nx>=0&&ny<H&&ny>=0&&str[nx][ny]!='*'){
                 if(str[nx][ny]=='C'){
                     //cout<<e<<" "<<nx<<" "<<ny<<endl;
                 }
                 if(str[nx][ny]=='C'&&!(BX==nx&&BY==ny)){  // 找到了
                     cout<<step<<endl;
                     return ; 
                 }
                 if(!visit[nx][ny]){  // 没遍历过的结点入队                  
                   p.x=nx;
                   p.y=ny;
                   p.step=step+1;
                   visit[nx][ny]=true;
                   Q.push(p);
                 }
                 nx+=Move[e][0];
                 ny+=Move[e][1];
             }

         }
     }
     

    
}
int main(){
    //freopen("test/D.txt","r",stdin);
    cin>>H>>W;
    for(int i = 0;i<W;++i){
        cin>>str[i];
    }
    for(int i = 0;i<W;++i){
        for(int j = 0;j<H;++j){
            visit[i][j]=false;
        }
    }
    // 选出开始结点
    bool flag=true;
    for(int i = 0;i<W;++i){
        for(int j = 0;j<H;++j){
            if(str[i][j]=='C'){
                visit[i][j]=true;
                BX=i;
                BY=j;
                flag=false;
                break;
            }
        }
        if(!flag){
            break;
        }
    }
    bfs();

}
#include<iostream>
#include<queue>
using namespace std;
bool visit[7][7];

long long ans=0;
int Move[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int N,M,T;
int SX,SY,FX,FY;
typedef struct Node
{
    int x;
    int y;
}Node;
Node node[100];
int nN=0;

void dfs(int x,int y){
     if(x==FX&&y==FY){
         ans++;
         return;
     }
     for(int e=0;e<4;++e){
         int nx=x+Move[e][0];
         int ny=y+Move[e][1];
         if(!visit[nx][ny]&&nx<=N&&nx>=1&&ny<=M&&ny>=1){
             visit[nx][ny]=true;
             node[nN].x=nx;
             node[nN++].y=ny;
            dfs(nx,ny);
            visit[nx][ny]=false;
            nN--;
         }
     }

}

int main(){
   // freopen("test/A.txt","r",stdin);
    cin>>N>>M>>T;
    cin>>SX>>SY>>FX>>FY;
    if(SX==FX&&SY==FY){
        cout<<0<<endl;
        return 0;
    }
    for(int i = 0;i<7;++i){
        for(int j = 0;j<7;++j){
            visit[i][j]=false;
        }
    }
    for(int i = 0;i<T;++i){
       int x, y;
       cin>>x>>y;
       visit[x][y]=true;   // 标记不可访问
    }
    visit[SX][SY]=true;
    dfs(SX,SY);
    cout<<ans<<endl;
    



}
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 110
int n,m,k;

int val[maxn][maxn];  // 有多少面积了
bool vis[maxn][maxn]; 
bool islake[maxn][maxn];  // 是否有效结点
int fa[maxn][maxn];   // 答案归结
int ans=0;
int moves[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
void bfs(int i,int j){
    queue<pair<int,int>> Q;
    pair<int,int> p(i,j);
    vis[i][j]=true;
    val[i][j]=1;
    Q.push(p);
    while(!Q.empty()){
        pair<int,int> q;
        q=Q.front();
        Q.pop();
        int x=q.first;
        int y=q.second;
        for(int e=0;e<4;++e){
            int nx=moves[e][0]+x;
            int ny=moves[e][1]+y;
            if(nx<1||nx>n||ny<1||ny>m){
                continue;
            }
            if(!vis[nx][ny]&&islake[nx][ny]){
                vis[nx][ny]=true;
                val[i][j]++;
                p.first=nx;
                p.second=ny;
                Q.push(p);
            }
        }
    }
}
int main(){
    freopen("test/A.in","r",stdin);
    cin>>n>>m>>k;
    for(int i = 1;i<maxn;++i){
        for(int j =1;j<maxn;++j){
            islake[i][j]=false;
            vis[i][j]=false;
            val[i][j]=0;
        }
    }
    for(int i = 0;i<k;++i){
       int x,y;
       cin>>x>>y;
       islake[x][y]=true;
    }
    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            if(!vis[i][j]&&islake[i][j]){
                bfs(i,j);
            }
        }
    }
    for(int  i = 1;i<=n;++i){
        for(int j =1;j<=m;++j){
            ans=max(ans,val[i][j]);
        }
    }

    cout<<ans<<endl;



}
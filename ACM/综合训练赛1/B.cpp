#include<iostream>
using namespace std;
#define maxn 200005
#define mod 1000000007
typedef struct{
    int to;
    int next;
}Edge; 

int head[maxn];
Edge edge[maxn];
int cnt=0;
void add_edge(int u,int v){
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;

}
int col[maxn];    // 颜色
long long dp[maxn][5];
int n,k;

void init(){
     for(int i = 0;i<maxn;++i){
         col[i]=0;
         head[i]=-1;
     }
     for(int i = 0;i<maxn;++i){
         for(int j =1;j<=3;++j){
             dp[i][j]=1;
         }
     }
}


// 记pre在参数记会好很多
void dfs(int x,int pre){
    // 如果这个点已经被染色
     if(col[x]!=0){
       dp[x][1]=dp[x][2]=dp[x][3]=0;
       dp[x][col[x]]=1;
     }

    // 先把孩子处理出来，从下到上dp
    for(int i = head[x];i!=-1;i=edge[i].next){
        int to =edge[i].to;
        if(to==pre){
            continue;
        }
        dfs(to,x);
        dp[x][1]=dp[x][1]*(dp[to][2]+dp[to][3])%mod;
        dp[x][2]=dp[x][2]*(dp[to][1]+dp[to][3])%mod;
        dp[x][3]=dp[x][3]*(dp[to][1]+dp[to][2])%mod;
    }
}

int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    // 先存双向边
    for(int i = 0;i<n-1;++i){
       int x,y;
       cin>>x>>y;
       add_edge(x,y);
       add_edge(y,x);
    }

    // 记录颜色
    for(int i = 0;i<k;++i){
        int x,y;
        cin>>x>>y;
        col[x]=y;
    }
    long long ans=0;
    dfs(1,0);
    ans=(dp[1][1]+dp[1][2]+dp[1][3])%mod;
    cout<<ans<<endl;
}
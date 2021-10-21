#include<iostream>
#include<queue>
using namespace std;
#define maxn 1000005
#define maxm 2000006
#define mod 100003

int head[maxn];

int dis[maxn];
long long num[maxn];  // 到达i的条数
bool vis[maxn];
typedef struct Edge
{
    int to;
    int next=-1;
    int w=1;
}Edge;
Edge edge[maxm];

int cnt = 0; 
void add_edge(int u,int v,int w){
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void init(){
    for(int i = 0;i<=maxn;++i){
        head[i]=-1;
        dis[i]=1000000000;
        num[i]=1;
    }
}

void spfa(int s){
     dis[s]=0;
     queue<int> Q;
     // 第一个结点入队
     Q.push(s);
     while(!Q.empty()){
         int p=Q.front();
         Q.pop();
         for(int i = head[p];i!=-1;i=edge[i].next){
             int to =edge[i].to;
             if(dis[to]>dis[p]+1){
                dis[to]=dis[p]+1;
                num[to]=num[p];
                Q.push(to);
             }else if(dis[to]==dis[p]+1){
                 num[to]+=num[p];
                 num[to]=num[to]%mod;
             }
         }
     }

}

int main(){
    freopen("test/b.in","r",stdin);
    init();
    int n,m;
    cin>>n>>m;
    for(int i = 0;i<m;++i){
       int u,v;
       cin>>u>>v;
       add_edge(u,v,1);
       add_edge(v,u,1);
    }
    // for(int i = head[1];i!=-1;i=edge[i].next){
    //     cout<<edge[i].to<<" ";
    // }
    // cout<<endl;
    spfa(1);

    for(int i = 1;i<=n;++i){
        if(dis[i]==1000000000){
            cout<<0<<endl;
        }else{
           cout<<num[i]%mod<<endl;
        }
        
    }
    
}
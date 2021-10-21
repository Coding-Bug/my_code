#include<iostream>
#include<queue>
using namespace std;
#define maxn 200004
#define maxm 300004

int head[maxn];
int dis[maxn];
int dfn[maxn];
typedef struct Edge
{
    int to;
    int next=-1;
    int w=1;
}Edge;
Edge edge[maxm];
int n,m;

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
        dfn[i]=0;
    }
}

bool spfa(int s){
     dis[s]=0;
     queue<int> Q;
     // 第一个结点入队
     Q.push(s);
     while(!Q.empty()){
         int p=Q.front();
         Q.pop();
         if(dfn[p]>n){
             return false;
         }
         for(int i = head[p];i!=-1;i=edge[i].next){
             int to =edge[i].to;
             int w=edge[i].w;
             if(dis[to]>dis[p]+w){
                dis[to]=dis[p]+w;
                dfn[to]=dfn[p]+1;
                Q.push(to);
             }
         }
     }
    return true;
}

int main(){
    //freopen("test/A.in","r",stdin);
    int T;
    cin>>T;
    
    while(T--){
        init();
        cin>>n>>m;
        for(int i = 0;i<m;++i){
            int u,v,w;
            cin>>u>>v>>w;
            
            add_edge(u,v,w);
            if(w>=0){
                add_edge(v,u,w);
            }
        }

        bool ans=spfa(1);
        if(ans){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
}
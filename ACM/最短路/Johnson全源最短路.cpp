#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 4008
#define maxm 10008
#define INF 1000000000
typedef struct Node
{
    int ver;
    int val;  // 因为要优先队列，所以设一个val
    bool operator <(const Node & a) const {
        return val>a.val;
    }
}Node;
typedef struct Edge
{
    int to;
    int next=-1;
    int w;
}Edge;
Edge edge[maxm+3];
int cnt=0;
int head[maxn+3]; // 头
long long dis[maxn+3]; // n的最短路
long long h[maxn+3];
int dfn[maxn+3];
int n,m;

void add_edge(int u,int v,long long  w){
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void init(){
    for(int i = 0;i<maxn;++i){
        head[i]=-1;
        dis[i]=INF;
        h[i]=0;
        dfn[i]=0;
    }
}

bool spfa(int s){
    queue<int> Q;
    h[s]=-1;
    dfn[s]=0;
    Q.push(s);
    while(!Q.empty()){
        int p=Q.front();
        Q.pop();
        if(dfn[p]>n){
            return false;
        }
        for(int i=head[p];i!=-1;i=edge[i].next){
            int to=edge[i].to;
            long long w=edge[i].w;
            if(h[to]>h[p]+w){
                dfn[to]=dfn[p]+1;
                h[to]=h[p]+w;
                Q.push(to);
            }
        }
    }
    return true;
}



void dijkstra(int s){
     priority_queue<Node> Q;
     Node p;
     p.ver=s;
     dis[s]=0;
     p.val=dis[s];
     Q.push(p);
     while(!Q.empty()){
         p = Q.top();
         Q.pop();
         long long  val = p.val;
         int ver=p.ver;
         if(val!=dis[ver]){
            continue;
         }
         for(int i = head[ver];i!=-1;i=edge[i].next){
             int to=edge[i].to;
             long long w=edge[i].w;
             if(dis[to]>dis[ver]+w){
                 dis[to]=dis[ver]+w;
                 p.ver=to;
                 p.val=dis[to];
                 Q.push(p);
             }
         }
     }
}

int main(){
    //freopen("test/C.in","r",stdin);
    init();
     cin>>n>>m;
     for(int i = 0;i<m;++i){
         int u,v;
         long long w;
         cin>>u>>v>>w;
         add_edge(u,v,w);
     }
 
     for(int i = 1;i<=n;++i){
         add_edge(0,i,0);
     }
     if(spfa(0)==false){
         cout<<"-1"<<endl;
         return 0;
     }

     // 构建新的边
     for(int i=1;i<=n;++i){
         for(int j =head[i];j!=-1;j=edge[j].next){
             int to =edge[j].to;
             long long w=edge[j].w;
             edge[j].w=h[i]+w-h[to];
         }
     }

     // 算最短路
    //  for(int i = 1;i<=n;++i){
    //      cout<<h[i]<<endl;
    //  }
     long long ans=0;
     for(int i = 1;i<=n;++i){
         for(int k = 1;k<=n;++k){
             dis[k]=INF;
         }
         ans=0;
         dijkstra(i);
         for(long long j= 1;j<=n;++j){ 
             if(dis[j]==INF){
                 //cout<<INF<<" ";
                 ans+=j*INF;
             }else{
                 //cout<<(dis[j]-h[i]+h[j])<<" ";
               ans+=(dis[j]-h[i]+h[j])*j;
             }
            
         }
          //cout<<endl;
        cout<<ans<<endl;
     }
}




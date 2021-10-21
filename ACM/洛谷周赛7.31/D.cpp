#include<iostream>
#include<queue>
using namespace std;
#define maxn 50005
#define maxm 2000005
#define INF 100000000000
typedef struct Node{
    int pos;
    unsigned long long val;
    bool operator < (const Node& a) const {
        return val>a.val;
    }
}Node;
typedef struct Edge
{
    int to;
    unsigned long long w;
    int next;
}Edge;

unsigned long long  dis[maxn];
Edge edge[maxm];
int head[maxn];
int cnt=0;
void add_edge(int u,int v,long long w){
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void init(){
     for(int i = 0;i<maxn;++i){
         head[i]=-1;
         dis[i]=INF;
     }
}

int n,m,q;
long long ans;

void dijstra(int s){
     dis[s]=0;
     priority_queue<Node> Q;
     Node p;
     p.pos=s;
     p.val=dis[s];
     Q.push(p);
     while(!Q.empty()){
         p=Q.top();
         Q.pop();
         unsigned long long val=p.val;
         int ver=p.pos;
         if(val!=dis[ver]){
            continue;
         }
         for(int i =head[ver];i!=-1;i=edge[i].next){
             int to=edge[i].to;
             unsigned long long w=edge[i].w;
             if(dis[to]>val+w){
                 dis[to]=val+w;
                 p.pos=to;
                 p.val=dis[to];
                 Q.push(p);
             }
         }
     }

}
int main(){
    //freopen("test/A.in","r",stdin);
    init();
    cin>>n>>m>>q;
    for(int i = 1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        if(u!=v){
            add_edge(v,u,w);
        }
    }
    
     
    dijstra(1);
   
    int A,B;
    for(int i = 1;i<=q;++i){
        
        cin>>A>>B;
        cout<<dis[A]+dis[B]<<endl;
    }

}
#include<iostream>
#include<queue>
using namespace std;
#define maxn 100004
#define maxm 500004   
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

Edge edge[maxm];
int cnt=0;
int head[maxn]; // 头
long long dis[maxn]; // n的最短路
void add_edge(int u,int v,int w){
     edge[cnt].to=v;
     edge[cnt].w=w;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}

priority_queue<Node> Q;
void dijkstra(int s){
    Node p;
    dis[s]=0;
    p.ver=s;
    p.val=dis[s];
    Q.push(p);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        int ver=p.ver;
        int val=p.val;
         if(val!=dis[ver]){  // 这个点之前已经出去了，这个是没更新到最小的时候的点
            continue; 
         }
    
        for(int i= head[ver];i!=-1;i=edge[i].next){
            int to = edge[i].to;
            int w=edge[i].w;
            if(dis[to]>val+w){
                dis[to]=val+w;
                p.val=dis[to];
                p.ver=to;
                Q.push(p);
            }
        }
    }
}


int main(){
    //freopen("test/A.in","r",stdin);

    for(int i = 0;i<maxn;++i){
        head[i]=-1;
          
    }
    int n,m,s;
    cin>>n>>m>>s;
    for(int i = 0;i<=n;++i){
        dis[i]=100000000100;
    }
    for(int i = 0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
    }
    dijkstra(s);
    for(int i=1;i<=n;++i){
        cout<<dis[i]<<" ";
    }
    cout<<endl;


}
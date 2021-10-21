#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define INF 1000000000
#define maxn 20000

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
    int next;
    int w;
}Edge;
Edge edge[maxn];
long long dis[maxn];
int cnt=0;
int N,A,B;
int ans=0;
int head[maxn];
bool vis[maxn];
void add_edge(int u,int v,int w){
     edge[cnt].to=v;
     edge[cnt].w=w;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}
void init(){
    for(int i=0;i<maxn;++i){
        head[i]=-1;
        dis[i]=INF;
        vis[i]=false;
    }
}

void dijkstra(int s){
    priority_queue<Node> Q;
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
        if(vis[ver]){
            continue;
        }
        if(ver==B){
           return;
        }
        vis[ver]=true;
        for(int i= head[ver];i!=-1;i=edge[i].next){
            int to = edge[i].to;
            int w=edge[i].w;
            if(dis[to]>=val+w){
                dis[to]=val+w;
                p.val=dis[to];
                p.ver=to;
                Q.push(p);
            }
        }
    }
}
int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>N>>A>>B;
    for(int i = 1;i<=N;++i){
        int K;
        int v;
        cin>>K;
        if(K!=0){
           cin>>v;
           add_edge(i,v,0);
           K--;
        }
        while(K--){
             cin>>v;
             add_edge(i,v,1);
        }
    }
    // 更新到A的距离
    for(int i=head[A];i!=-1;i=edge[i].next){
        dis[edge[i].to]=edge[i].w;
    }
    dijkstra(A);
    //cout<<dis[1]<<" "<<dis[2]<<" "<<dis[3]<<endl;
    if(dis[B]==INF){
        cout<<"-1"<<endl;
    }else{
        cout<<dis[B]<<endl;
    }
}
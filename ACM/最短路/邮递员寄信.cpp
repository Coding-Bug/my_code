#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 1004
#define maxm 100004
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
long long ans=0;

int head2[maxn];  // 返图
long long dis2[maxn];
Edge edge2[maxm];
int cnt2=0;
void add_edge(int u,int v,int w){
     edge[cnt].to=v;
     edge[cnt].w=w;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}
void add_edge2(int u,int v,int w){
     edge2[cnt2].to=v;
     edge2[cnt2].w=w;
     edge2[cnt2].next=head2[u];
     head2[u]=cnt2++;
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

void dijkstra2(int s){
    priority_queue<Node> Q;
    Node p;
    dis2[s]=0;
    p.ver=s;
    p.val=dis2[s];
    Q.push(p);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        int ver=p.ver;
        int val=p.val;
         if(val!=dis2[ver]){  // 这个点之前已经出去了，这个是没更新到最小的时候的点
            continue; 
         }
    
        for(int i= head2[ver];i!=-1;i=edge2[i].next){
            int to = edge2[i].to;
            int w=edge2[i].w;
            if(dis2[to]>val+w){
                dis2[to]=val+w;
                p.val=dis2[to];
                p.ver=to;
                Q.push(p);
            }
        }
    }
}

int main(){
    //freopen("test/A.in","r",stdin);
    for(int i = 0;i<maxn;++i){
        dis[i]=100000000;
        head[i]=-1;
        head2[i]=-1;
        dis2[i]=100000000;
    }
    int n,m;
    cin>>n>>m;
    for(int i = 0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge2(v,u,w);

    }
    dijkstra(1);
    dijkstra2(1);
     for(int i = 1;i<=n;++i){
         ans+=dis[i]+dis2[i];
     }

    cout<<ans<<endl;

}
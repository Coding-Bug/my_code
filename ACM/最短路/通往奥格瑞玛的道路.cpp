#include<iostream>
using namespace std;
#include<queue>
#define maxn 10004
#define maxm 50004
const long long maxdis=1e17; 
int head[maxn];
long long  dis[maxn];
long long f[maxn];   // 要交的钱
// 输入
int n,m;
long long b;
// 答案区间
long long l=1e18;
long long r=0;
long long mid;
typedef struct Edge
{
    int to;
    long long w;
    int next;
}Edge;
typedef struct Node
{
    int ver;
    int val;
    bool operator <(const Node &a) const{
        return val>a.val;
    }
}Node;
int cnt=0;
Edge edge[2*maxm];
void add_edge(int u,int v,long long w){
    edge[cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void init(){
    for(int i = 0;i<maxn;++i){
        head[i]=-1;
        dis[i]=maxdis;
    }
}
// 因为用到点权，所以用dijkstra
bool dijkstra(int s){
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
          long long val=p.val;
          
          if(dis[ver]!=val){   // dijkstra重要的一个东西
              continue;
          }
          for(int i = head[ver];i!=-1;i=edge[i].next){
              int to =edge[i].to;
              long long w=edge[i].w;
              if(f[to]>mid){   //如果这个判断放在外面，那么最大值即使到不了，也会被更新dis
                  continue;
              }
              if(dis[to]>val+w&&val+w<b){
                      dis[to]=val+w;
                      p.val=dis[to];
                      p.ver=to;
                      Q.push(p);
                }
          }
      }
      // 判断能否到达
      if(dis[n]==maxdis){
          return false;
      }else{
          return true;
      }
}
int main(){
    //freopen("test/E.in","r",stdin);
    init();
    cin>>n>>m>>b;
    for(int i = 1;i<=n;++i){
        cin>>f[i];
        if(f[i]>r){
            r=f[i];
        }
        if(f[i]<l){
            l=f[i];
        }
    }
    // for(int i = 1;i<=n;++i){
    //     cout<<f[i]<<" ";
    // }cout<<endl;
    for(int i = 0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
        if(u!=v){       // 双向公路
            add_edge(v,u,w);
        }
    }
    // 求得是收费最大的最小值，这种就是二分
    // 二分答案
    mid=r;
    if(!dijkstra(1)){
       cout<<"AFK"<<endl;
       return 0;
    }
    while(l<=r){

        // 重新设置dis
        mid=(r+l)/2;
        for(int i = 0;i<=n;++i){
           dis[i]=maxdis;
        }
        if(dijkstra(1)){   // 如果这个答案能跑，则把答案分小
           if(r-l==2){
               r=mid;
               continue;
           }
           if(r-l==1){
                mid=l;
                break;
            }
           r=mid;
        }else{
            if(r-l==1){
                mid=r;
                break;
            }
           l=mid+1;
        }
    } 
    cout<<mid<<endl;
    
}
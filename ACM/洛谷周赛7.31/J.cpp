#include<iostream>
#include<queue>
using namespace std;
#define maxn 1004
#define maxm 1000005
#define mod 9987
#define INF 1000000000003
typedef struct Dis{
    unsigned long long d;
    unsigned long long n;   // 求余了多少次
}Dis;
typedef struct Node{
    int pos;
    Dis val;
    bool operator < (const Node& a) const {
        if(val.n==a.val.n){    // 同样求余这么多次
           return val.d >a.val.d;
        }else{
           return val.n>a.val.n;
        }
    }
}Node;
typedef struct Edge
{
    int to;
    unsigned long long w;
    int next;
}Edge;



Dis dis[maxn];
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
         dis[i].d=INF;
         dis[i].n=0;
     }
}

int n,m;
long long ans;

void dijstra(int s){
     dis[s].d=1;
     dis[s].n=0;
     priority_queue<Node> Q;
     Node p;
     p.pos=s;
     p.val=dis[s];
     Q.push(p);
     while(!Q.empty()){
         p=Q.top();
         Q.pop();
         Dis val=p.val;
         int ver=p.pos;
         if(dis[ver].n!=val.n||dis[ver].d!=val.d){   // 结点出去过了
             continue;
         }
         for(int i =head[ver];i!=-1;i=edge[i].next){
             int to=edge[i].to;
             unsigned long long w=edge[i].w;
             
             // 求松弛的结果
             int un=val.n;
             if(un!=0&&val.d==0){
                 val.d=1;
             }
             unsigned long long ud=val.d*w;
             if(ud>=mod){
                un+=ud/mod;
                ud=ud%mod;
             }
             
             int vn=dis[to].n;
             unsigned long long vd=dis[to].d;
             if(vd>=mod){
                vn+=ud/mod;
                vd=ud%mod;
             }
             bool flag=false;    // 判断用不用更新
             if(w==0){
                 ud=0;
                 un=0;
             }
             if(dis[to].d==INF){
                flag=true;
             }else{
                 if(un==vn){
                     if(ud<vd){
                         flag=true;
                     }
                 }else{
                     if(un<vn){
                         flag=true;
                     }
                 }
             }
             if(flag){
                 dis[to].n=un;
                 dis[to].d=ud;
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
    cin>>n>>m;
    for(int i = 1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w);
    }

    dijstra(1);
    ans=dis[n].d%mod;
    cout<<ans<<endl;

}
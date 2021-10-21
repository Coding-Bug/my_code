#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
#define maxn 500000
typedef struct Edge
{
    int u;
    int v;
    double w;
    bool operator <(const Edge& a) const{
        return w>a.w;
    }
}Edge;
typedef struct{
    int x;
    int y;
    
}Node;
Edge edge[maxn];
Node node[maxn];
int f[maxn];     // 并查集
int cnt=0;
int s=0;
int n=0;
double ans=0;


double cal(Node a ,Node b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void init(){
    for(int i =0;i<maxn;++i){
        f[i]=i;
    }
}

int find(int x){
    if(f[x]==x){
        return x;
    }
    f[x]=find(f[x]);
    return f[x];
}

void Union(int x,int y){
    if(f[x]==f[y]){
        return;
    }
    f[find(x)]=find(y);
}

// 最小生成树
// n是需要几条边
double tree(int N){
    int num=0;// 找到了几条边
        priority_queue<Edge> Q;
        for(int i =0;i<cnt;++i){
            Q.push(edge[i]);
        }
        while(!Q.empty()){
            Edge p;
            p=Q.top();
            Q.pop();
            if(find(p.u)!=find(p.v)){
               Union(p.u,p.v);
               num++;
               if(num==N){
                   return p.w;
               }
            }

        }
        return 0;
}



int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>s>>n;
    for(int i = 1;i<=n;++i){
        cin>>node[i].x>>node[i].y;
    }
    for(int i  =1;i<=n;++i){
        for(int j=i+1;j<=n;++j){
        double temp=cal(node[i],node[j]);
        edge[cnt].u=i;
        edge[cnt].v=j;
        edge[cnt++].w=temp;
        }
    }
    
    ans=tree((n-s));
    printf("%.2f\n",ans);
}
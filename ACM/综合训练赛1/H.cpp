#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 4000000
typedef struct Edge {
      int u;
      int v;
      long long  w;
}Edge;

bool cmp(Edge a,Edge b){
    return a.w<b.w;
}
typedef struct 
{
    double x;
    double y;
}P;


P pon[maxn];
Edge edge[maxn]; 
int cnt=0;   // 边数

int f[maxn];

void init(){
    for(int i = 0;i<maxn;++i){
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
long long cal(P a,P b){
    return ((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y));
}
int n,c;

int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>n>>c;
    for(int i = 0;i<n;++i){
        cin>>pon[i].x>>pon[i].y;
    }
    for(int i = 0;i<n;++i){
        for(int j= i+1;j<n;++j){
            edge[cnt].u=i;
            edge[cnt].v=j;
            edge[cnt].w=cal(pon[i],pon[j]);
            cnt++;
        }
    }

    sort(edge,edge+cnt,cmp);
    long long ans=0;
    for(int i = 0;i<cnt;++i){
        Edge p=edge[i];
        if(p.w<c){
            continue;
        }
         if(find(p.u)!=find(p.v)){
            Union(p.u,p.v);
            ans+=p.w;
         }
    }
    
    for(int i = 1;i<n;++i){
        if(find(i)!=find(i-1)){
            cout<<"-1"<<endl;
            return 0;
        }
    }
    cout<<ans<<endl;
}
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 5004
#define maxm 200005

int f[maxn];
typedef struct Edge{
    int u;
    int v;
    int w;
}Edge;
bool cmp(Edge a,Edge b){
    return a.w<b.w;
}
Edge edge[maxm];
int find(int x){
     if(f[x]==x){
         return x;
     }
     f[x]=find(f[x]);
     return f[x];
}
void Union(int x,int y){
    if(f[x]==f[y]){
        return ;
    }
    f[find(x)]=find(y);
}

int n,m;
int main(){
    //freopen("test/B.in","r",stdin);
    for(int i=0;i<maxn;++i){
       f[i]=i;
    }
    cin>>n>>m;
    for(int i = 0;i<m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        edge[i].u=u;
        edge[i].v=v;
        edge[i].w=w;
    }
    sort(edge,edge+m,cmp);
    int ans=0;
    for(int i = 0;i<m;++i){
        Edge p=edge[i];
        if(f[p.u]!=f[p.v]){
            Union(p.u,p.v);
            ans+=p.w;
            for(int j =1;j<=n;++j){
                find(j);    // 一定要更新一波
            }
        }
    }
    for(int i = 2;i<=n;++i){
        if(f[i]!=f[i-1]){
            cout<<"orz"<<endl;
            return 0;
        }
    }
    cout<<ans<<endl;
    

    

}
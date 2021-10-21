#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 10004
#define maxm 50004
#define INF 1000000000
int f[maxn];
int n,m,q;
int ans;
typedef struct Edge{
    int u;
    int v;
    int w;
}Edge;
Edge edge[maxn];
Edge tree[maxn];
int cnt=0;      // 树中边的个数


bool cmp(Edge a,Edge b){
    return a.w>b.w;
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
        return ;
    }
    f[find(x)]=find(y);
}
void Kruskal(){
     for(int i = 0;i<m;++i){
         Edge p=edge[i];
         if(f[p.u]!=f[p.v]){
             Union(p.u,p.v);
             for(int i =1;i<=n;++i){
                 tree[cnt++]=p;      // 向树中加一条边      
                 find(i);
             }
         }
     }
}

// 求最近公共祖先
void targin(){

}

int main(){
    freopen("test/A.txt","r",stdin);
    cin>>n>>m;
    for(int i = 0;i<=n;++i){
        f[i]=i;
    }
    for(int i=0;i<m;++i){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }

    // 由大到小排个序
    sort(edge,edge+m,cmp);
    cin>>q;
    while(q--){
        ans=INF;
        int x,y;
        cin>>x>>y;
        if (f[x]!=f[y]){     // 不连通
            cout<<"-1"<<endl;
            continue;
        }



    }


    
}
#include<iostream>
#include<queue>
using namespace std;
#define ll long long
#define maxn 50010
const ll mod=201314;

ll fa[maxn][23];
vector<ll> child[maxn];
ll dep[maxn];
ll n,q;

// 获取所有结点的深度,并预处理2^k个父亲
void get_dep(){
     queue<int> Q;
     Q.push(0);
     dep[0]=1;
     while(!Q.empty()){
       int q=Q.front();
       Q.pop();

       for(auto ch:child[q]){
         dep[ch]=dep[q]+1;
         for(int k =1;k<20;++k){
           fa[ch][k]=fa[fa[ch][k-1]][k-1];
         }
         Q.push(ch);
       }
     }
}


// 查询x,y的最近公共祖先
ll query(int x,int y){
  if(dep[x]<dep[y]){
    swap(x,y);
  }
  
  // 跳到相同深度

  for(int k=20;k>=0;--k){
    if(dep[fa[x][k]]>=dep[y]){
      x=fa[x][k];
    }
  }

  if(x==y){
    return x;
  }

  // 一起跳到公共祖先
  for(int k =20;k>=0;--k){
    if(fa[x][k]!=fa[y][k]){
                                                                                                                                                                      
      x=fa[x][k];
      y=fa[y][k];
    }
  }
  
  //再往上一格
  return fa[y][0];
}
                                                                                                                                                                                                                                    
int main(){
  //freopen("test/LCA.txt","r",stdin);
  cin>>n>>q;
  for(int i=1;i<n;++i){
    cin>>fa[i][0];
    child[fa[i][0]].push_back(i);
  }

  get_dep();   // 获取每个节点深
  while(q--){
    ll l,r,z;
    cin>>l>>r>>z;
    ll ans=0;
    for(int i=l;i<=r;++i){
      int lca=query(i,z);
      ans+=dep[lca]%mod;
    }
    cout<<ans<<endl;
  }

}
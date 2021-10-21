#include<iostream>
using namespace std;
#define maxn 200005
#define ll long long
ll a[maxn];
ll b[maxn];   // 差分
ll ans=0;     // 记录N点的温度
ll n,q,s,t;
int main(){
    freopen("test/A.in","r",stdin);
    scanf("%lld%lld%lld%lld",&n,&q,&s,&t);
    for(int i = 0;i<=n;++i){
       scanf("%lld",&a[i]);
    }

    for(int i = 1;i<=n;++i){
        b[i]=a[i]-a[i-1];
    }

    // 先算出原来的温度
    for(int i =1;i<=n;++i){
        if(b[i]>0){
            ans+=-b[i]*s;
        }else if(b[i]<0){
            ans+=-1*b[i]*t;
        }
    }
     
    int u,v;
    ll w;
    while(q--){
        scanf("%d%d%lld",&u,&v,&w);
        // 减去u,v+1的前缀贡献
        if(b[u]>0){
            ans-=-b[u]*s;
        }else{
            ans-=-1*b[u]*t;
        }
        if(v<n){
            if(b[v+1]>0){
                ans-=-b[v+1]*s;
            }else{
                ans-=-1*b[v+1]*t;
            }
        }

        // 改变差分
        b[u]+=w;
        if(v<n){
            b[v+1]-=w;
        }

        // 加上u，v的前缀贡献
         if(b[u]>0){
            ans+=-b[u]*s;
        }else{
            ans+=-1*b[u]*t;
        }
        if(v<n){
            if(b[v+1]>0){
                ans+=-b[v+1]*s;
            }else{
                ans+=-1*b[v+1]*t;
            }
        }
        cout<<ans<<endl;
    }

}
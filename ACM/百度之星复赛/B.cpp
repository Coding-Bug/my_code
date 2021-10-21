#include<iostream>
using namespace std;
#define ll long long 
const ll mod=1e9 +7;
int t;
int n,m;

ll init(ll base,int p){
       ll ans=1;
       while(p){
       if(p%2!=0){
           ans=(ans*base)%mod;
       }
       
       base=(base*base)%mod;
       p=p/2;
       }

       return ans%mod;
}

ll fac(ll n){
    ll ans=1;
    while(n!=0){
        ans=(ans*n)%mod;
        n--;
    }
    return ans%mod;
}

ll com(ll n, ll r){
    ll ans=1;
    ll base = init(fac(r)*fac(n-r)%mod,mod-2);
    ll top = fac(n);
    ans=base*top%mod;
    return ans;

}
int main(){
    freopen("test/A.in","r",stdin);
    scanf("%d",&t);
    while(t--){
       scanf("%d%d",&n,&m);
       ll fa=fac(n);
       ll in=com(n,m);
       ll ans=(fa*in)%mod;
       cout<<ans<<endl;
    }

}
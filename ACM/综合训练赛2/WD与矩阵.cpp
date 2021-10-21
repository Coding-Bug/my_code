#include<iostream>
using namespace std;
#define ll long long 
const ll mod=998244353;
int t;
int n,m;


ll init(unsigned long long base,unsigned long long p){
    unsigned long long ans=1;
    while(p){
    if(p%2!=0){
        ans=(ans*base)%mod;
    }

    p/=2;
    base=(base*base)%mod;
    }
    return ans%mod;


}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n>>m;
        ll ans1=init(2,(m-1));
        cout<<init(ans1,n-1)<<endl;
    }
}
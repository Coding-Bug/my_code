#include<iostream>
using namespace std;
#define ll long long


ll n,k;

int t;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n>>k;
        ll ans=0;
        ll now=1;
        ll temp=0;
        while(now<n){
            if(now<k){
                temp=now;
            }else{
                temp=k;
            }
            if(temp==k){
               temp=n-now;
               if(temp%k==0){
                   ans+=temp/k;
               }else{
                   ans+=temp/k+1;
               }
               break;
            }

            now+=temp;
            ans++;
        }
        cout<<ans<<endl;

    }

}
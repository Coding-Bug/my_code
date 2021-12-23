#include<iostream>
using namespace std;
#define ll long long
int t;
ll x,y;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>x>>y;
        ll ans;
        if(x>y){
            ans=x+y;
            cout<<ans<<endl;
        }else{
            ans=y-(y%x/2);
            cout<<ans<<endl;
        }

    }

}
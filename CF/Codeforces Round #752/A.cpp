#include<iostream>
using namespace std;
#define maxn 110
#define ll long long
int a[maxn];

int t,n;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n;
        ll ans=0;
        for(int i = 1;i<=n;++i){
            cin>>a[i];
        }
        
        ll pos =1;
        for(int i =1;i<=n;++i){
            if(a[i]>pos){
                ans+=a[i]-pos;
                pos+=a[i]-pos;
            }
            pos++;
        }
        cout<<ans<<endl;

    }
}
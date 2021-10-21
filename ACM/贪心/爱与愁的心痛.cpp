#include<iostream>
using namespace std;
#define maxn 3994
int n,m;
int sum[maxn];
int ans=1e9;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    int a; 
    for(int i=1;i<=n;++i){
        cin>>a;
        sum[i]=sum[i-1]+a;
    }
    for(int i = m;i<=n;++i){
        if((sum[i]-sum[i-m])<ans){
            ans=(sum[i]-sum[i-m]);
        }
    }

    cout<<ans<<endl;


}
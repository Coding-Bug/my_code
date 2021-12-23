#include<iostream>
using namespace std;
#define maxn 100010
#define ll long long
ll n;
ll a[maxn];


int t;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        ll meg=0;
        cin>>n;
        for(int  i=1;i<=n;++i){
            cin>>a[i];
        }
        for(int i=2;i<=n;++i){
            if(a[i]<=a[i-1]){
                meg++;
            }
        }
        if(n%2==0){
            cout<<"YES"<<endl;
        }else if(meg>0){
            cout<<"YES"<<endl;

        }else{
            cout<<"NO"<<endl;
        }
    }

}
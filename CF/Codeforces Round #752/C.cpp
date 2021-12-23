#include<iostream>
using namespace std;
#define maxn 100010
#define  ll long long
int t,n;
ll a[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n;
        ll MAX=0; // 最多往前多少
        ll MIN=0; // 最少往前多少
        bool ans=true;
        int pos;
        for(int i =1;i<=n;++i){
            cin>>a[i];
        }
        
        bool flag;
        for(int i=1;i<=n;++i){
             flag=true;  // 先假设从1到i+1都能整除它
            for(int  j =1;j<=i+1;++j){
                if(a[i]%j!=0){
                    flag=false;
                    break;
                }
            }
            if(flag){
                break;
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
        
    }

}
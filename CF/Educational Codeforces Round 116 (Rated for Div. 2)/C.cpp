#include<iostream>
#include<cstring>
using namespace std;
#define ll long long
#define maxn 12
int t,n;
ll bank_de[maxn];
ll k;

// 求10的k次方
ll fuc(int k){
    ll ans=10;
    for(int i =0;i<k-1;++i){
        ans*=10;
    }
    return ans;
}

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        bank_de[1]=1;
        cin>>n>>k;
        int a;
        cin>>a;
        for(int i =2;i<=n;++i){
            cin>>a;
            bank_de[i]=fuc(a);
        }
        ll ans=0;
        ll sum=k+1;   // 一共用k+1张构造
        for(int i = 1;i<=n;++i){
            if(sum==0){
                break;
            }
            // 第n种取掉剩下的所有张
            if(i==n){
                ans+=sum*bank_de[n];
                break;
            }

            // 非第n种尽量取最多
            if(sum>bank_de[i+1]/bank_de[i]-1){
                ans+=(bank_de[i+1]/bank_de[i]-1)*bank_de[i];
                sum-=bank_de[i+1]/bank_de[i]-1;
            }else{
                ans+=sum*bank_de[i];
                break;
            }
        }

        cout<<ans<<endl;


        

    }

}
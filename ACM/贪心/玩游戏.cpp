#include<iostream>
using namespace std;
#define ll long long
#define maxn 100005
ll a,b;
ll sum[maxn];
ll ans[maxn];
int cnt=0;
int main(){
    //freopen("test/A.in","r",stdin);
    // 预处理出前缀和
    for(int i =1;i<maxn;++i){
        sum[i]=sum[i-1]+i;
    }

    cin>>a>>b;
    int n;
    for(int i = 1;i<maxn;++i){
        if(a+b==sum[i]){
            n=i;
            cout<<n<<" ";
            break;
        }
        if(a+b<sum[i]){
            cout<<"No";
            return 0;
        }
    }
    
    ll tempa=a;
    ll tempb=b;
    

    // 从后面的方法
    for(int i = n;i>=1;--i){
        if(tempa>=i){
           tempa-=i;
           ans[cnt++]=i;
        } 
    }
    for(int i =cnt-1;i>0;--i){
        cout<<ans[i]<<" ";
    }

    // 从前面不行
    // for(int i =1;i<=n;++i){
    //     if(tempa>=i){
    //         ans[cnt++]=i;
    //         tempa-=i;
    //     }
    // }

    // for(int i=0;i<cnt-1;++i){
    //     cout<<ans[i]<<" ";
    // }
    // cout<<ans[cnt-1];

    
}
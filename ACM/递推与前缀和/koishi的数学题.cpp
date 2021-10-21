#include<iostream>
using namespace std;
#define maxn 1000005
#define ll long long

int prime[maxn];
int cnt=0;
bool isprime[maxn];
ll f[maxn];    // 存因数和
ll g[maxn];    // 第一个质因子的结果
ll ans[maxn];
int n;

// 预处理出因数和
void cal(){
    isprime[0]=isprime[1]=true;
    for(int i = 2;i<=n;++i){
        if(isprime[i]){
            prime[cnt++]=i;
            f[i]=i+1;
            g[i]=i+1;
        }

        for(int j=0;j<cnt&&i*prime[j]<=n;++j){
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0){
                g[i*prime[j]]=g[i]*prime[j]+1;
                f[i*prime[j]]=f[i]/g[i]*g[i*prime[j]];
                break;
            }
            g[i*prime[j]]=g[prime[j]];
            f[i*prime[j]]=f[i]*g[prime[j]];
            }
    }
}



int main(){
    //freopen("test/A.in","r",stdin);
    for(int i = 0;i<maxn;++i){
        isprime[i]=true;
    }
    cin>>n;
    cal();
    ans[1]=n-1;
    for(int i = 2;i<=n;++i){
        ans[i]=ans[i-1]-f[i]+n;
    }
    for(int i =1;i<=n;++i){
        cout<<ans[i]<<" ";
    }
    cout<<endl;


}



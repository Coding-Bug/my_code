#include<iostream>
using namespace std;
#define maxn 4000
#define maxw 13000
int w[maxn],d[maxn];  // w是占用空间,d是价值
int dp[maxw]; //dp[i][j]是前i个商品，剩余容量为j的情况,压缩空间，不然会mme
int n,m;
void solve(){
    for(int i=1;i<=n;++i){
        for(int j = m;j>=w[i];--j){
                dp[j]=max(dp[j-w[i]]+d[i],dp[j]);
        }
    }
    cout<<dp[m]<<endl;
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    for(int i = 1;i<=n;++i){
        cin>>w[i]>>d[i];
    }
    solve();
}
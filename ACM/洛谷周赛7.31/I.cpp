#include<iostream>
using namespace std;
#define maxn 305
long long a[maxn];
int n;
long long dp[maxn][maxn];  // dp[i][j]是从第i个数合并到第j个数的最大值
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i=0;i<maxn;++i){
        for(int j = 0;j<maxn;++j){
            dp[i][j]=0;
        }
    }
    long long ans=0;
    for(int i = 0;i<n;++i){
        cin>>a[i];
        dp[i][i]=a[i];
    }
    int i,j;
    
    for(int len = 2; len<=n;++len){
        for( i = 0, j=i+len-1; i<n&&j<n; ++i,j=i+len-1){
        for(int k = i;k<j;++k){
            if(dp[i][k]==dp[k+1][j]){
                dp[i][j]=max(dp[i][j],dp[i][k]+1);
                ans=max(ans,dp[i][j]);
                
            }
        }
        }
    }
    cout<<ans<<endl;
}
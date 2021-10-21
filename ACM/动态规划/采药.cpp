#include<iostream>
using namespace std;
#define maxm 105
#define maxt 5005
int T,M;
int v[maxm];
int w[maxm];
int dp[maxm][maxt];
int main(){
    freopen("test/A.in","r",stdin);
    cin>>M>>T;
    for(int i = 0;i<=T;++i){
        dp[0][i]=0;
    }
    for(int i = 0;i<=M;++i){
        dp[i][0]=0;
    }
    for(int i = 1;i<=M;++i){
        cin>>v[i]>>w[i];
    }
    for(int i = 1;i<=M;++i){
        for(int j = 1;j<=T;++j){
            if(j-v[i]>=0){
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i]]+w[i]);
            }else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    cout<<dp[M][T]<<endl;
}
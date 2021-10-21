#include<iostream>
#include<cstring>
using namespace std;
#define maxs 2005
char A[maxs];
char B[maxs];
int dp[maxs][maxs];
int main(){
    //freopen("test/A.txt","r",stdin);
    dp[0][0]=0;
    for(int i = 0;i<maxs;++i){
        dp[0][i]=i;
        dp[i][0]=i;
    }
    cin>>A;
    cin>>B;
    int lenA=strlen(A);
    int lenB=strlen(B);
    // 动态规划
    for(int i = 1;i<=lenA;++i){
        for(int j = 1;j<=lenB;++j){
            if(A[i-1]==B[j-1]){
                dp[i][j]=dp[i-1][j-1];
            }else{
                    dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]+1);
                    dp[i][j]=min(dp[i][j],dp[i][j-1]+1);    
            }
        }
    }
    cout<<dp[lenA][lenB]<<endl;
}
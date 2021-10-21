#include<bits\stdc++.h>
using namespace std;
int main(){
    //freopen("test/C.txt","r",stdin);
    int A[23][1003];    
    int dp[23][1003];
    int C;    // 数据组数
    int n,m; // 行数和列数
    cin>>C;
    while(C!=0){
        cin>>n>>m;
        for(int i = 1;i<=n;++i){
            for(int j = 1;j<=m;++j){
                cin>>A[i][j];
            }
        }

        for(int i = 0;i<=22;++i){
            for(int j = 0;j<=1002;++j){
                dp[i][j]=-20000020;
            }
        }

        // 进行dp
        dp[0][1]=0;
        for(int i =1;i<=n;++i){
            for(int j = 1;j<=m;++j){
                dp[i][j]=max(dp[i-1][j],dp[i][j-1])+A[i][j];
                for(int k = 1;k<j;++k){
                    if(j%k==0)
                    dp[i][j]=max(dp[i][j],dp[i][k]+A[i][j]);
                }
            }
        }

        // for(int i = 1;i<=n;++i){
        //     for(int j = 1;j<=m;++j){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }

        cout<<dp[n][m]<<endl;
        C--;

    }

}
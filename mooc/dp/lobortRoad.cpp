#include<bits/stdc++.h>
using namespace std;
int main(){
    //freopen("test/C.txt","r",stdin);
    int m,n;    // m乘n矩阵
    cin>>m>>n;
    int ans=0;  // 路径个数

    // 动态创建dp数组
    int **dp = new int*[m+1];
    for(int i = 0;i<=m;++i){
        dp[i] = new int[n+1];
    }

    // 初始化边界
    for(int i = 0;i<=n;++i){
        dp[0][i]=0; 
    }
    for(int j = 0;j<=m;j++){
        dp[j][0]=0;
    }

    dp[0][1]=1;    // 为了下面初始化dp[1][1];
    // 求dp路径
    for(int i = 1;i<=m;++i){
        for(int j = 1;j<=n;++j){
            dp[i][j]=dp[i][j-1]+dp[i-1][j];
        }
    }
    cout<<dp[m][n];



}
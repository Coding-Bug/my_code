#include<iostream>
using namespace std;
// dp求解
const long long mod = 1e9+7;
int n ,m;
long long dp[53][53];
int main(){
    // 初值
    dp[1][1]=1;
    dp[0][0]=1;   // 这个状态设为1，不然会影响只有右子数或者只有左子树的情况
    // 打出所有的情况
    for(int i = 2;i<=50;++i){   // i=1的其他情况全是0
        for(int j = 1;j<i;++j){
            // 将树分割成左子树和右子数
            // x,y是左子树的结点数和叶子节点数
            for(int x=0;x<i;++x){
                for(int y=0;y<=x;++y){
                    if(j-y<0){  //不限制则会越界，越界会得带乱七八糟的结果
                        continue;
                    }
                   dp[i][j]=(dp[i][j]+dp[x][y]*dp[i-x-1][j-y]%mod)%mod;
                }
            }
            //scout<<i<<" "<<j<<" "<<dp[i][j]<<endl; 
           
        }
        // if(i==5){
        //     break;
        // }
    }
    while(scanf("%d%d",&n,&m)!=EOF){
        cout<<dp[n][m]%mod<<endl;
    }
    return 0;
}
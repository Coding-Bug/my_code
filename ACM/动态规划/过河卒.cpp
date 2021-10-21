#include<iostream>
using namespace std;
bool canvis[22][22];
long long  dp[22][22];    // 竟然爆longlong
int Move[8][2]={{2,1},{2,-1},{1,2},{1,-2},{-2,1},{-2,-1},{-1,2},{-1,-2}};
int main(){
    //freopen("test/A.in","r",stdin);
    int n,m;
    int cx,cy;
    for(int i = 0;i<22;++i){
        for(int j = 0;j<22;++j){
            canvis[i][j]=true;
        }
    }
    cin>>n>>m>>cx>>cy;
    canvis[cx][cy]=false;
    // 把马给干了
    for(int e=0;e<8;++e){
        int nx=cx+Move[e][0];
        int ny=cy+Move[e][1];
        if(nx>=0&&nx<=n&&ny>=0&&ny<=m){
            canvis[nx][ny]=false;
        }
    }
    if(!canvis[0][0]){
        cout<<0<<endl;
        return 0;
    }
    dp[0][0]=1;
    for(int i = 1;i<=m;++i){
        if(!canvis[0][i]){
            dp[0][i]=0;
        }else{
        dp[0][i]=dp[0][i-1];
        }
    }
    for(int j = 1;j<=n;++j){
        if(!canvis[j][0]){
            dp[j][0]=0;
        }else{
          dp[j][0]=dp[j-1][0];
        }
    }
    

    for(int i =1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            if(!canvis[i][j]){
                dp[i][j]=0;
            }else{
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
    }
    

    cout<<dp[n][m]<<endl;


}
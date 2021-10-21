#include<iostream>
using namespace std;
#define maxn 1004
int dp[maxn][maxn]={0};
bool canvis[maxn][maxn];
int n,t;
int ans=0;
int main(){
    for(int i = 0;i<maxn;++i){
        for(int j =0;j<maxn;++j){
            canvis[i][j]=true;
            dp[i][j]=0;
        }
    }
    //freopen("test/A.in","r",stdin);
    cin>>n>>t;
    for(int i = 0;i<t;++i){
        int x,y;
        cin>>x>>y;
        canvis[x][y]=false;
    }
    
    // 初始化第一行
    for(int j=1;j<=n;++j){
        if(canvis[1][j]){
            dp[1][j]=1;
        }else{
            dp[1][j]=0;
        }
    }
    for(int i=1;i<=n;++i){
        if(canvis[i][1]){
            dp[i][1]=1;
            ans=1;
        }else{
            dp[i][1]=0;
        }
    }

    for(int i = 2;i<=n;++i){
        for(int j = 2;j<=n;++j){
            if(!canvis[i][j]){
                dp[i][j]=0;
                continue;
            }
            int a=dp[i-1][j];
            int b=dp[i][j-1];
            if(a==b){
                if(canvis[i-a][j-a]){
                    dp[i][j]=a+1;
                }else{
                    dp[i][j]=a;
                }
            }else{
                a=min(a,b);
                dp[i][j]=a+1;
            }
            ans=max(dp[i][j],ans);
            
        }
    }

    // for(int i = 1;i<=n;++i){
    //     for(int j = 1;j<=n;++j){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<ans<<endl;





}
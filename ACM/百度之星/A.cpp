#include<iostream>
using namespace std;
#define maxn 14
int t=0;
int n=0;
int dp[maxn][maxn];
char str[maxn][maxn];
void init(){
    for(int i=0;i<maxn;++i){
        for(int j = 0;j<maxn;++j){
            dp[i][j]=0;
        }
    }
}
int main(){
    freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n;
        init();
        for(int i = 1;i<=n;++i){
            cin>>str[i];
        }
        
        if(str[1][1]!='#'){
            dp[1][1]=1;
        }
        for(int i = 2;i<=n;++i){
            if(str[1][i]!='#'){
                dp[1][i]=dp[1][i-1];
            }
            if(str[i][1]!='#'){
                dp[i][1]=dp[i-1][1];
            }
        }

        for(int i = 2;i<=n;++i){
            for(int j=2;j<=n;++j){
                if(str[i][j]!='#'){
                    dp[i][j]=dp[i-1][j]+dp[i][j-1];
                }
            }
        }
        cout<<dp[n][n]<<endl;

    }
    
}
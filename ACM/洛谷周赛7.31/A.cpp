#include<iostream>
using namespace std;
#define maxn 1004
int a[maxn];
int v[maxn];
int s;
int dp[maxn][maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>s;
    a[1]=0;
    a[0]=0;
    v[0]=0;
    v[1]=1;
    for(int i = 2;i<=s;++i){
        a[i]=0;
        v[i]=i;
    }
    for(int i =2;i<=s;++i){
        for(int j = 1;j*j<=i;++j){
            if(i%j==0){
                if(j!=1&&j*j!=i){
                a[i]+=j+i/j;
                }else{
                    a[i]+=j;
                }
            }
        }
    }
    // for(int i = 0;i<=s;++i){
    //     cout<<i<<" "<<a[i]<<endl;
    // }
    for(int i = 0;i<=s;++i){
        dp[i][0]=0;
        dp[0][i]=0;
    }

    for(int i = 1;i<=s;++i){
        for(int j = 1;j<=s;++j){
            if(j<v[i]){
                dp[i][j]=dp[i-1][j];
            }else{
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-v[i]]+a[i]);
            }
        }
    }
    // for(int i = 1;i<=s;++i){
    //     cout<<dp[i]<<endl;
    // }
    // cout<<dp[9][10]<<endl;
    // cout<<"*******"<<endl;
    // for(int i = 0;i<=s;++i){
    //     cout<<i<<" "<<dp[i][i]<<endl;
    // }
    cout<<dp[s][s]<<endl;



}
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 1004
int m,n;

// 分组结构体
typedef struct Grop{
    int v[maxn];
    int w[maxn];
    int num=1;  // 组内的物品个数
}Grop;

Grop grop[maxn];

int dp[maxn][maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>m>>n;
    int maxc=0;
    for(int i = 1;i<=n;++i){
        int v,w,c;
        cin>>v>>w>>c;
        if(c>maxc){
            maxc=c;
        }
        int num=grop[c].num;
        grop[c].v[num]=v;
        grop[c].w[num]=w;
        grop[c].num++;
    }
    for(int i = 0;i<=maxc;++i){
        dp[i][0]=0;
    }
    for(int j =0;j<=m;++j){
        dp[0][j]=0;
    }
    for(int i = 1;i<=maxc;++i){     // 组别
       for(int j = 1;j<=m;++j){
           for(int k = 1;k<grop[i].num;++k){
               if(j>=grop[i].v[k]){
                   int temp=max(dp[i-1][j],dp[i-1][j-grop[i].v[k]]+grop[i].w[k]);
                   dp[i][j]=max(temp,dp[i][j]);
               }else{
                   dp[i][j]=max(dp[i-1][j],dp[i][j]);
               }
           }
       }  

    }
    cout<<dp[maxc][m]<<endl;
}
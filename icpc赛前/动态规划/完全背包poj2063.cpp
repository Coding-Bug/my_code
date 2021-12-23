#include<iostream>
using namespace std;
#define maxm   500000
#define maxn   1200
int n,m,y;  // n是物品数，m是最大容量，y是多少年
int w[maxn],d[maxn];
int dp[maxm];

void solve(){
    for(int i= 1;i<=n;++i){
        for(int j =0;j<=m;++j){
            if(w[i]<=j){
                dp[j]=max(dp[j-w[i]]+d[i],dp[j]);
            }
        }
    }
}
int t;
int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&m,&y);
        scanf("%d",&n);
        int ans=m;
        int temp=0;
        for(int i =1;i<=n;++i){
            scanf("%d%d",&w[i],&d[i]);
            w[i]/=1000;
        }
        m/=1000;
        while(y--){
            for(int i=0;i<maxm;++i){
                dp[i]=0;
            }
            solve();
            temp+=dp[m];
            m=(ans+temp)/1000;
        }
        printf("%d\n",ans+temp);
    }
}
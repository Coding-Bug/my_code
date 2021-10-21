#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#define maxn 100000
typedef struct Term
{
    int v;
    int w;
}Term;

Term term[maxn];
int cnt=1;
int dp[2][maxn];  // 滚
int n;
int T;   // 总时间
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>T;
    // 要用那个分组法
    for(int i = 1;i<=n;++i){
        int v,w,p;
        cin>>w>>v>>p;
        if(p==0){   // 如果是无限次看的，要转化
           p=T/v;
        }
        // 分离
        int k=1;
        for(int i = 1;i<=p;i=pow(2,k),k++){
            term[cnt].v=v*i;
            term[cnt].w=w*i;
            cnt++;
            p-=i;
        }
        if(p!=0){
            term[cnt].v=v*p;
            term[cnt].w=w*p;
            cnt++;
        }
    }

    dp[1][0]=dp[0][0]=0;
    for(int i = 0;i<=T;++i){
        dp[0][i]=0;
    }


    for(int i = 1;i<cnt;++i){
        for(int j = 1;j<=T;++j){
            if(term[i].v<=j){
                dp[i%2][j]=max(dp[(i-1)%2][j],dp[(i-1)%2][j-term[i].v]+term[i].w);
            }else{
                dp[i%2][j]=dp[(i-1)%2][j];
            }
        }
    }

    cout<<dp[(cnt-1)%2][T]<<endl;






}
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
int dp[2][maxn];  // 滚动
int hs,ms;   // 开始的几时几分
int he,me;   // 结束的几时几分
char str[8];
int n;
int T;   // 总时间
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>str;  // 开始的时间
    // 计算开始的分钟数
    bool flag=true;
    hs=0;
    ms=0;
    int k=1;
    for(int i = strlen(str)-1;i>=0;--i){
        if(flag){   // 计算分钟
           if(str[i]==':'){
               flag=false;
               k=1;
               continue;
           }
           ms+=int(str[i]-48)*k;
           k=10;
        }else{
           hs+=int(str[i]-48)*k;
           k=10;
        }
    }

    cin>>str;
     flag=true;
    he=0;
    me=0;
    k=1;
    for(int i = strlen(str)-1;i>=0;--i){
        if(flag){   // 计算分钟
           if(str[i]==':'){
               flag=false;
               k=1;
               continue;
           }
           me+=int(str[i]-48)*k;
           k=10;
        }else{
           he+=int(str[i]-48)*k;
           k=10;
        }
    }
    
    T=(he-hs)*60+me-ms;
    cin>>n;

    // 要用那个分组法
    for(int i = 1;i<=n;++i){
        int v,w,p;
        cin>>v>>w>>p;
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
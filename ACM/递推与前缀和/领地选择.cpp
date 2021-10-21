#include<iostream>
using namespace std;
#define maxn 1004
int a[maxn][maxn];
int sum[maxn][maxn];  // 前缀和
int n,m,c;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m>>c;
    for(int i =1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            cin>>a[i][j];
        }
    }

    for(int  i =1;i<=n;++i){
        for(int j =1;j<=m;++j){
            sum[i][j]=a[i][j]+sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        }
    }
    int ans=-1e9;
    int ansi,ansj;
    int len=c;
    for(int i = 0;i<=n;++i){
       for(int j =0;j<=m;++j){
          if(i+len>n||j+len>m){
              continue;
          }

          int x2=i+len;
          int y2=j+len;
          if(sum[x2][y2]-sum[x2][j]-sum[i][y2]+sum[i][j]>ans){
              ansi=i+1;
              ansj=j+1;
              ans=sum[x2][y2]-sum[x2][j]-sum[i][y2]+sum[i][j];
          }
       }
    }
    cout<<ansi<<" "<<ansj<<endl;
}
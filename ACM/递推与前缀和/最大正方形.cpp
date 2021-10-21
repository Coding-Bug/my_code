#include<iostream>
using namespace std;
#define maxn 104
int n,m;
int a[maxn][maxn];   // 原矩阵
int sum[maxn][maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    for(int i = 1;i<=n;++i){
        for(int j =1;j<=m;++j){
            cin>>a[i][j];
        }
    }


    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    }
    int ans=0;
    for(int x1=0;x1<=n;++x1){
        for(int y1=0;y1<=m;++y1){
            int len=0;
            while(true){   
                len++;
                if(x1+len>n||y1+len>m){
                    break;
                }     
                int x2=x1+len;
                int y2=y1+len;    
                    if(sum[x2][y2]-sum[x2][y1]-sum[x1][y2]+sum[x1][y1]==len*len){
                        if(len>ans){
                            ans=len;
                        }
                    }
            }
            
        }
    }
    cout<<ans<<endl;





}
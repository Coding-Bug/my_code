#include<iostream>
#include<unordered_map>
using namespace std;
#define maxn 55
long long b[2]={13,131};   // 两个b分别管理两维

int n;     // 矩阵大小
int matA[maxn][maxn];
int matB[maxn][maxn];
long long hsA[maxn][maxn];
long long hsB[maxn][maxn];
unordered_map<long long ,int> mp;

// 快速幂
long long cal(long long base,int p){
          long long ans=1;
          while(p>0){
              if(p%2!=0){
                  ans*=base;
              }
              base*=base;
              p/=2;
          }

          return ans;
}
// 制造二维哈希
void make_hash(int  str[][maxn],long long hs[][maxn],int n){
    for(int i=0;i<=n;++i){
        hs[i][0]=0;
        hs[0][i]=0;
    }
     // 行哈希
     for(int i = 1,c;i<=n;++i){
         for(int j =1;j<=n;++j){
             c=str[i][j];
             hs[i][j]=hs[i][j-1]*b[0]+c;
         }
     }
     // 列哈希
     for(int i=1;i<=n;++i){
         for(int j = 1;j<=n;++j){
             hs[i][j]=hs[i-1][j]*b[1]+hs[i][j];
         }
     }
}


// 获取子矩阵的哈希值
// x,y是子矩阵右下角的坐标
// 由于是矩阵，所以只用传个len即可
long long get_subhs(long long hs[][maxn],int x,int y,int len){  
          long long i=cal(b[0],len);
          long long j=cal(b[1],len);
          return hs[x][y]
          -hs[x-len][y]*j
          -hs[x][y-len]*i
          +hs[x-len][y-len]*i*j;
          
}


int main(){
    //freopen("test/B.in","r",stdin);
    
    cin>>n;
    for(int i = 1;i<=n;++i){
        for(int j =1;j<=n;++j){
            cin>>matA[i][j];
        }
    }

    for(int i = 1;i<=n;++i){
        for(int j =1;j<=n;++j){
            cin>>matB[i][j];
        }
    }
    make_hash(matA,hsA,n);   // 先把A的哈希做出来
    
    // for(int i = 1;i<=n;++i){
    //     for(int j =1;j<=n;++j){
    //         cout<<hsA[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"******************"<<endl;
    make_hash(matB,hsB,n);
    // for(int i = 1;i<=n;++i){
    //     for(int j =1;j<=n;++j){
    //         cout<<hsB[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"******************"<<endl;
    int l=0;
    int r=n+1;
    int len;
    // 二分长度求解
    while(l<r){
        //cout<<l<<" "<<r<<endl;
        len=(l+r)/2; 
        mp.clear();
        bool flag=false;  // 是否找到相同的子串
        // 处理出所以A中该长度的子串
        for(int i = 1;i<=n;++i){
            for(int j =1;j<=n;++j){
                if(j-len<0||i-len<0){
                    continue;
                }
                long long hA=get_subhs(hsA,i,j,len);
                //cout<<hA<<endl;
                mp[hA]=2;
            }
        }

        //cout<<"*********"<<endl;
        for(int i = 1;i<=n;++i){
            for(int j =1;j<=n;++j){
                if(j-len<0||i-len<0){
                    continue;
                }
                long long hB=get_subhs(hsB,i,j,len);
                //cout<<hB<<endl;
                if(mp.count(hB)!=0){
                    flag=true;
                    break;
                }
            }
            if(flag){
                break;
            }
        }
        
        if(!flag){    // 不行的话就减小
            r=len;
        }else{
            if(l==r-1){
                break;
            }
            l=len;
        }
    }

    cout<<len<<endl;

}
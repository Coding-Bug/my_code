#include <bits/stdc++.h>
using namespace std;
#define maxn 100004
#define maxk 30
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int Lg[maxn]; // log 2 
int ST[maxn][maxk];
int n;
int m;    // 长度为n，m次询问
void In_it(){
    for(int j = 0;j<maxn;++j){
            Lg[j]=0;
    }
}


// 预处理st
void Init_ans(){
     // 求log
     for(int i = 2;i<=maxn;++i){
         Lg[i]=Lg[i>>1]+1;
     }

     for(int j = 1;j<=Lg[n];++j){
         for(int i = 1;i+(1<<j)-1<=n;++i){
              ST[i][j]=min(ST[i][j-1],ST[i+(1<<(j-1))][j-1]);
         }
     }
}  

int qu_ans(int l,int r){
    int x=Lg[r-l];
    return min(ST[l][x],ST[r-(1<<x)+1][x]);
}


int main(){
    //freopen("test/A.in","r",stdin);
    n=read();
    m=read();
    In_it();
    // 输入的时候直接放表里
    for(int i=1;i<=n;++i){
        ST[i][0]=read();
        //scanf("%d",&st[i][0]);
    }
    Init_ans();   // 预处理
    // for(int i = 1;i<=n;++i){
    //     for(int j=i;j<=n;++j){
    //        cout<<i<<" "<<j<<" "<<ans_search(i,j)<<endl;
    //     }
    // }
    for(int i = 1;i<=n-m+1;++i){
        cout<<qu_ans(i,i+m-1)<<endl;
    }
    return 0;

}
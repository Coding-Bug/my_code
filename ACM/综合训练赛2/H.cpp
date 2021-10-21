#include<iostream>
using namespace std;
#define maxn 505
int m,k;
int S[maxn]={0};
int L;     // 最多那个人最少的区间长度
int l,r;
int ans=1000000000;
int main(){
    cin>>m>>k;
    int a;
    for(int i = 1;i<=m;++i){
        cin>>a;
        S[i]=S[i-1]+1;
    }
    if(m%k==0){
        L=m/k;
    }else{
        L=m/k+1;
    }

    for(int i = m;i>=L-1;--i){
        if(S[i]-S[i-L-1]<ans){
            ans=S[i]-S[i-L];
            r=i;
            l=i-L;
        }
    }

    





    

    


}
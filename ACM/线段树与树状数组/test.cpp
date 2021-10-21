#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100

int main(){
    int A[maxn]={8,20,30,4,-20,4};
    int B[maxn];
    int C[maxn];
    int n=6;

    for(int i = 0;i<n;++i){
        B[i]=A[i];
    }
    sort(B,B+n);      // 排序
    int L=unique(B,B+n)-B;  // 去重
    // 存排名
    for(int i = 0;i<n;++i){
    C[i]=lower_bound(B,B+L,A[i])-B+1;
    
    }
    for(int i = 0;i<6;++i){
        cout<<C[i]<<" ";
    }
    cout<<endl;
}


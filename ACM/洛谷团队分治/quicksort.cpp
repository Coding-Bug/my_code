#include<iostream>
using namespace std;
#include<time.h>
#define MAX 100005
int N;
int A[MAX];
// 快排也是有很大得优化空间的！
// 全部相等的情况下，相当于没有分治
int Sort(int l ,int r){
    // 三数取中法
    int p=(l+r)/2;
    int temp=A[l];
    A[l]=A[p];
    A[p]=temp;
    p=A[l];
    while(l<r){
        while(l<r&&A[r]>=p){
            r--;
        }
        A[l]=A[r];
        while(l<r&&A[l]<=p){
            l++;
        }
        A[r]=A[l];

    }
    A[l]=p;
    return l;
}
void quick_sort(int l,int r){
     if(l>=r){
         return;
     }
     int k=Sort(l,r);
     // 元素聚集
     int lr=k;
     int rl=k;
     while(lr>l&&A[lr]==A[k]){
         lr--;
     }
     while(rl<r&&A[rl]==A[k]){
         rl++;
     }
     if(lr>l) quick_sort(l,lr); //左边排序
     if(rl<r) quick_sort(rl,r); // 右边排序
     
}
int main(){
    //freopen("test/A2.txt","r",stdin);
    cin>>N;
    for(int i = 0;i<N;++i){
        cin>>A[i];
    }
    quick_sort(0,N-1);
    for(int i = 0;i<N;++i){
        cout<<A[i]<<" ";
    }
    cout<<endl;
}
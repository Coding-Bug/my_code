#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100003
#define mod 99999997 
typedef struct Node{
    int pos;   // 初始的位置
    int val;   // 初始值
}Node;
Node x[maxn];
Node y[maxn];
int c[maxn];
bool cmp(Node a,Node b){
    if(a.val==b.val){
        return a.pos<b.pos;
    }
    return a.val<b.val;
}
int n;

long long ans=0;
// 归并
void merge_sort(int l,int r){ 
    if(l>=r){
        return;
    }
    int mid=(l+r)/2;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    // 合并
    int i =l;
    int j=mid+1;
    int Temp[maxn];   // 中间数组
    int cnt=0;
    while(i<=mid&&j<=r){
         if(c[i]<=c[j]){
            Temp[cnt++]=c[i++];
         }else{
            Temp[cnt++]=c[j++];
            // 此时有逆序对
            ans+=mid-i+1;
            ans=ans%mod;
            
         }
         
    }
    while(i<=mid){
        Temp[cnt++]=c[i++];
    }
    while(j<=r){
        Temp[cnt++]=c[j++];
    }
    for(int k=0;k<cnt;++k){
        c[l+k]=Temp[k];
    }
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i = 0;i<n;++i){
        cin>>x[i].val;
        x[i].pos=i;
    }
    for(int i = 0;i<n;++i){
        cin>>y[i].val;
        y[i].pos=i;
    }
    // 两个数组都从小到大排序
    sort(x,x+n,cmp);
    sort(y,y+n,cmp);
    // y数组每个原位置应该交换到的位置
    for(int i = 0;i<n;++i){
        c[y[i].pos]=x[i].pos;
    }
    
    // 通过归并找逆序对，并不是真的是要排序，只是借助排序找逆序对
    merge_sort(0,n-1);
    // for(int i = 0;i<n;++i){
    //     cout<<c[i]<<" ";
    // }
    // cout<<endl;

    cout<<ans<<endl;




}
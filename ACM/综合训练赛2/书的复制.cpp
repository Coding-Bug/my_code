#include<iostream>
using namespace std;
#define maxn 504
int n,k;
int a[maxn];
int ans[maxn];
int cnt=0;
int sum=0;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    int l=0;
    int r=1e9;
    int mid;
    while(l<=r){
         mid=(l+r)/2;
         cnt=1;  // 有多少个断点
         sum=a[n];
         ans[cnt-1]=n;
         for(int i =n-1;i>=1;--i){
             if(sum+a[i]>mid){
                 ans[cnt++]=i;  //记终点
                 sum=a[i];
             }else{
                 sum+=a[i];
             }
         }
        if(l==r){
            break;
        }
        if(cnt<=k){
            r=mid;
         }else {
             if(r==l+1){
                 l=r;
                 continue;
             }
            l=mid;
        }
        
    }
    cout<<1<<" "<<ans[cnt-1]<<endl;
    int i=cnt-1;
    while(i>0){
         cout<<ans[i]+1<<" ";
         --i;
         cout<<ans[i]<<endl;
    }

}
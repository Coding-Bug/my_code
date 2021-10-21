#include<iostream>
using namespace std;
// 最大字段和，用分治法来求
int n;
long long a[200004];
long long ans=0;   
// 求最大连续子段和
long long substr(int l,int r){
    if(l>r){
        return -1e9;
    }
     if(l==r){
         return a[l];
     }
     int mid=(l+r)/2;   // 中间值
     long long S1=substr(l,mid); // 求左边
     long long S2=substr(mid+1,r); // 求右边
     long long S=max(S1,S2);  
     long long S3=-1e9;
     //求中间
     int p;
     p=mid;
     long long sum=0;
     while(p>=l){
         sum+=a[p];
         if(sum>S3){
             S3=sum;
         }
         --p;
     }

     sum=S3;
     p=mid+1;
     while(p<=r){
         sum+=a[p];
         if(sum>S3){
             S3=sum;
         }
         ++p;
     }
     return max(S,S3);

}
int main(){
    //freopen("test/A.txt","r",stdin);
   cin>>n;
   for(int i = 0;i<n;++i){
       cin>>a[i];
   }
   ans=substr(0,n-1);
   cout<<ans<<endl;
}
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
// 直接用桶+暴力
#define MAX 1000003
int N;
int p[MAX]={0};
int ans[MAX];
int A[MAX];

//直接搜，这个就不优化了，优化也是优化到根号，
// 不用怕有的根本没有值会浪费
// 你排序一遍比这个更浪费时间
void cal(int a){
     for(int i = 1;i*i<=a;++i){
         if(p[i]!=0&&a%i==0){
            ans[a]+=p[i];
            int temp=a/i;
            if(temp!=i){
            ans[a]+=p[a/i];
            }
         }
     }

}
int main(){
    
   //freopen("test/A.in","r",stdin);
   cin>>N;
   memset(ans,-1,MAX);
   for(int i = 0;i<N;++i){
       cin>>A[i];
       p[A[i]]++;
   }
   
   for(int i = 0;i<N;++i){
       if(ans[A[i]]!=-1){
         cout<<ans[A[i]]<<endl;
       }else{
         cal(A[i]);
         cout<<ans[A[i]]<<endl;
       }
   }

   


}
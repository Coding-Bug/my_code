#include<iostream>
using namespace std;
#define maxn 100005
#define ll long long 
int T;
int m;
ll a1[maxn];
ll a2[maxn];
ll c1[maxn];
ll c2[maxn];
ll b[maxn];
ll tmp[maxn];
ll k[maxn];
 

bool judge(){
    
      
}

int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&T);
    while(T--){
         scanf("%d",&m);
         for(int i =1;i<=m;++i){
             scanf("%lld",&a1[i]);
         }
         for(int i =1;i<=m;++i){
             scanf("%lld",&a2[i]);
         }
         for(int i =1;i<=m;++i){
             scanf("%lld",&b[i]);
         }
         if(judge()){
             printf("2\n");
         }else{
             printf("1\n");
         }
         
    }

}
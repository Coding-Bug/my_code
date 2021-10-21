#include<iostream>
#include<unordered_map>
using namespace std;
#define maxn 5003
int pre[maxn];
int dp[maxn];
int a[maxn];
void init(){
    for(int i = 0;i<maxn;++i){
        pre[i]=-1;
        dp[i]=1;
    }
}


long long ans=0;
int main(){
    freopen("test/A.in","r",stdin); 
    int n;
    cin>>n;
    for(int i = 0;i<n;++i){
        cin>>a[i];
    }
    for(int j=0;j<n;++j){
        for(int i = 0;i<j;++i){
            if(a[j]<a[i]){
                if(dp[j]<dp[i]+1){
                    dp[j]=dp[i]+1;
                    pre[j]=i;
                }
            }
        }
    }

    for(int j=0;j<n;++j){
        

    }




}
#include<iostream>
using namespace std;
#define MAX 10000001
bool isprime[MAX+1];
long long phi[MAX+1];
long long prime[MAX+1];
long long Sum[MAX+1];   // 存放
int cnt=0;
void eulerSieve(){
    for(int i = 2;i<=MAX;++i){
        if(isprime[i]){
            phi[i]=i-1;
            prime[cnt++]=i;
        }
        for(int j=0;j<cnt&&i*prime[j]<=MAX;++j){
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
               break;
            }
             phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
long long ans=0;
int main(){
    //freopen("test/H.out","r",stdin);
    int n;
    cin>>n;
    for(int i = 0;i<=MAX;++i){
        isprime[i]=true;
    }
    eulerSieve();
    Sum[1]=1;
    for(int i = 2;i<=MAX;++i){
        Sum[i]=Sum[i-1]+phi[i];
    }
    // for(int i = 1;i<4;++i){
    //    cout<<Sum[i]<<endl;
    // }
    for(int i = 0;i<cnt&&prime[i]<=n;++i){
        ans+=2*Sum[(n/prime[i])]-1;  // 1,1会被重复两次
    }
    cout<<ans<<endl;
   

  
}
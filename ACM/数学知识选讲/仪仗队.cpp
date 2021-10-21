#include<iostream>
using namespace std;
#define MAX 16000003
int N;
bool isprime[MAX];
int ans=0;
int prime[MAX];
int cnt=0;
int phi[MAX];
void eulerSieve(){
    for(int i = 2;i<=N;++i){
        if(isprime[i]){
            prime[cnt++]=i;
        }
        for(int j=0;j<cnt&&i*prime[j]<=N;++j){
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0){
                phi[i*prime[j]]=phi[i]*prime[j];
               break;
            }
            phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
}
int main(){
    for(int i = 2;i<MAX;++i){
        phi[i]=i-1;
    }
    cin>>N;
    if(N==1){
        cout<<0<<endl;
        return 0;
    }
    for(int i = 0;i<MAX;++i){
        isprime[i]=true;
    }
    eulerSieve();
    phi[1]=1;
    for(int i =0;i<N;++i){
        ans+=phi[i];
    }
    cout<<2*ans+1<<endl;

}
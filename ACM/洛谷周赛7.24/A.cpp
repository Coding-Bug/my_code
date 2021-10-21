#include<iostream>
using namespace std;
#define MAX 100000
long long n;
bool isprime[MAX+1];
int prime[MAX+1];
int cnt=0;
void eulerSieve(){
    for(int i = 2;i<=MAX;++i){
        if(isprime[i]){
            prime[cnt++]=i;
        }
        for(int j=0;j<cnt&&i*prime[j]<=MAX;++j){
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0){
               
               break;
            }
        }
    }
}
int main(){
    for(int i = 0;i<=MAX;++i){
        isprime[i]=true;
    }
    eulerSieve();
    long long N;
    cin>>N;
        for(int j = 0;j<cnt;++j){
            bool flag=false;
            if(N%prime[j]==0){
                long long temp=N/prime[j];
                for(int i = 2;i*i<=temp;++i){
                    if(temp%i==0){
                        flag=true;
                        break;
                    }
                }
                if(!flag){
                    cout<<temp<<endl;
                    return 0;
                }
            }
        }
}
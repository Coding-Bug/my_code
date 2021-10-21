#include<iostream>
using namespace std;
#define MAX 100
long long N;
long long beg;  // 表的开头
long long g[MAX];
bool isprime[MAX];
long long  prime[MAX];
long long  cnt=0;
long long ans=0; //答案
void  eulerSieve(){
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
void cal(){
    long long M=0;   // 存放之前的最大约数个数
    for(;beg<=N;++beg){
        long long sum=1;
        long long k=beg;
        for(int j=0;j<cnt;++j){
            if(k%prime[j]!=0){
               continue;
            }
            int Count=1;   // 某个约数占的个数
            while(k!=1){
                if(k%prime[j]==0){
                   Count++;
                   k=k/prime[j]; 
                }else{
                    break;
                }
            }
            sum*=Count;
            if(k==1){
                // if(i==1||i==2||i==3||i==4||i==6){
                //     cout<<i<<" "<<sum<<endl;
                // }
                if(sum>M){
                    M=sum;
                    ans=beg;
                    cout<<ans<<",";
                }
                break;
            }
        }
    }
}
int main(){
    //freopen("test/A.out","w",stdout);
    for(int i = 0;i<=MAX;++i){
        isprime[i]=true;
    }
    eulerSieve();
    beg=1;
    N=2000000000;
    cal();
}
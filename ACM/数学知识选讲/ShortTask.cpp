#include<iostream>
#include<algorithm>
using namespace std;
#define MAX 10000000
int t;
int c;
bool isprime[MAX+1];
int prime[MAX+1];
int MAP[10000007];
typedef struct Node
{
    long long sum;
    int pos;
}Node;
Node p[MAX+1];
int cnt=0;
void  eulerSieve(){
      for(int i = 2;i<=MAX;++i){
          if(isprime[i]){
             p[i].sum=i+1;
             p[i].pos=i;
             prime[cnt++]=i;
          }
          for(int j=0;j<cnt&&i*prime[j]<=MAX;++j){
              isprime[i*prime[j]]=false;
              
              p[i*prime[j]].pos=i*prime[j];
              if(i%prime[j]==0){
                  p[i*prime[j]].sum=p[i].sum+(p[i].sum-p[(i/prime[j])].sum)*prime[j];
                  break;
              }
              p[i*prime[j]].sum=p[i].sum+p[i].sum*prime[j];
          }
      }
}

int main(){
    //freopen("test/A.in","r",stdin);
    for(int i = 0;i<MAX;++i){
        isprime[i]=true;
    }
    p[0].sum=0;
    p[0].pos=0;
    p[1].sum=1;
    p[1].pos=1;
    p[2].sum=3;
    p[2].pos=2;
    eulerSieve();
    // 构造map
    for(int i = 0;i<10000005;++i){
        MAP[i]=-1;
    }
    for(int i = 0;i<MAX;++i){
        if(p[i].sum<10000004){
            if(MAP[p[i].sum]==-1){    // 得到过的就不再取，因为要求最小i
            MAP[p[i].sum]=p[i].pos;
            }
        }
    }
    cin>>t;
    while(t--){
        cin>>c;
        cout<<MAP[c]<<endl;
         
    }
} 
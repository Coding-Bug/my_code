#include<iostream>
using namespace std;
#define maxn 100005
int f[maxn];
bool isprime[maxn];
int prime[maxn];
int cnt=0;
int Index=0;
int a,b,p;

void Euler(){
    for(int i = 2;i<maxn;++i){
        if(isprime[i]){
            prime[cnt++]=i;
        }
        for(int j = 0;j<cnt&&i*prime[j]<maxn;++j){
            isprime[i*prime[j]]=false;
            
            if(i%prime[j]==0){
               break;
            }
        }
    }
}



void init(){
     for(int i = 0;i<maxn;++i){
         f[i]=i;
         isprime[i]=true;

     }
}
int find(int x){
    if(f[x]==x){
        return x;
    }
    f[x]=find(f[x]);
    return f[x];
}

void Union(int x,int y){
     if(f[x]==f[y]){
         return;
     }
     f[find(x)]=find(y);
}
int main(){
    //freopen("test/A.in","r",stdin);
    init();
    cin>>a>>b>>p;
    Euler();    // 算出质数
    // 记录比p大的最小质数的位置
    for(int i = 0;i<cnt;++i){
        if(prime[i]>=p){
           Index=i;
           break;
        }
    }
    // 两两合并直接转换成质数合并
    // 这个要求重复筛选，不能只被最小的质数因子筛选
    for(int i = Index;i<cnt&&prime[i]<=b;++i){
       for(int j = 1;j*prime[i]<=b;++j){
              Union(prime[i],j*prime[i]);
       }
    }
    for(int i = a;i<=b;++i){
        find(i);    // 最后还是要再做一遍
    }
    int ans=0;
    for(int i = a;i<=b;++i){
        if(f[i]==i){
           ans++;
        }
    }
    cout<<ans<<endl;

    


}
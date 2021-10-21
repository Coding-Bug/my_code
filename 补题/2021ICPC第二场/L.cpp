#include<iostream>
#include<cstring>
using namespace std;
#define maxn 500005   // 结点的个数
#define max_prime 200
#define ll long long
const ll mod=998244353;

ll Sum[maxn];   // 求和
ll Mul[maxn];   // 懒标记
ll a[maxn];     // 源数据
ll A[maxn];     // 存放数据生成的欧拉函数值
bool isprime[maxn];
ll prime[maxn];
ll ph[maxn];   // 存放欧拉函数值
bool hav[maxn][max_prime];   // 某个结点是否含有某个素数
int n,m;
int op;   // 操作种类
int cnt=0;    // 素数值

// 欧拉函数
void Euler(){
   for(int i=2;i<max_prime;++i){
     if(isprime[i]){
        ph[i]=i-1;
        prime[cnt++]=i;
     }
     for(int j=0;j<cnt&&i*prime[j]<max_prime;++j){
       isprime[i*prime[j]]=false;
       if(i%prime[j]==0){
         ph[i*prime[j]]=ph[i]*prime[j];
         break;
       }
       ph[i*prime[j]]=ph[i]*(prime[j]-1);
     }
   }
}

// 向上求和
void PushUp(int rt){
  //cout<<rt<<"*"<<Sum[rt*2]<<"*"<<Sum[rt*2+1]<<endl;
  Sum[rt]=(Sum[rt*2]+Sum[rt*2+1])%mod;

  // 更新这个区间是否全存在某个质银子
  for(int i = 0;i<26;++i){
     if(hav[rt*2][prime[i]]&&hav[rt*2+1][prime[i]]){
       hav[rt][prime[i]]=true;
     }
  }
}

// 构建
void Build(int l,int r,int rt){
    if(r==l){
      Sum[rt]=A[r];
      for(int i = 0;prime[i]<=a[r];++i){
        if(a[r]%prime[i]==0){
           hav[rt][prime[i]]=true;
        }
      }
      return;
    }
   int m=(l+r)/2;
   Build(l,m,rt*2);
   Build(m+1,r,rt*2+1);
   PushUp(rt);
}

// 初始化
void init(){
    memset(isprime,true,sizeof(isprime));
    for(int i = 0;i<maxn;++i){
      Sum[i]=0;
      Mul[i]=1;
    }
    for(int i = 1;i<maxn;++i){
      ph[i]=i;
    }
    // 求欧拉函数值
    Euler();
    for(int i = 1;i<maxn;++i){
      for(int j=0;j<max_prime;++j){
       hav[i][j]=false;
      }
    }
    
    
    for(int i =1;i<=n;++i){
      A[i]=ph[a[i]];
    }
    // 构建线段树
    Build(1,n,1);
}



// 向下传递
void PushDowm(int rt){
    Sum[rt*2]=(Sum[rt*2]*Mul[rt])%mod;
    Mul[rt*2]=Mul[rt*2]*Mul[rt]%mod;
    Sum[rt*2+1]=(Sum[rt*2+1]*Mul[rt])%mod;
    Mul[rt*2+1]=Mul[rt*2+1]*Mul[rt]%mod;
    Mul[rt]=1;
}

// 区间更新
void Update(int L,int R,ll C, int l,int r,int rt){
     // 在区间内部
     if(r<=R&&l>=L){
       //cout<<l<<" "<<r<<endl;
        // 如果这个区间的数都有这个素数，则更新该区间
        if(hav[rt][C]){
          Sum[rt]=(Sum[rt]*C)%mod;
          Mul[rt]=Mul[rt]*C%mod;
          //cout<<"*1*"<<Sum[rt]<<" "<<Mul[rt]<<endl;
          return;
        }else{
          
          if(l==r){
            Sum[rt]=(Sum[rt]*ph[C])%mod;
            hav[rt][C]=true;
            Mul[rt]=1;
            //cout<<"*2*"<<Sum[rt]<<" "<<Mul[rt]<<endl;
            return;
          }
        }
     }

     int m=(l+r)/2;
     if(Mul[rt]!=1)
     PushDowm(rt);   // 先向下传递
     if(m>=L){
       Update(L,R,C,l,m,rt*2);
     }
     if(R>m){
       Update(L,R,C,m+1,r,rt*2+1);
     }
     PushUp(rt);
}


// 区间查询
ll Query(int L,int R, int l,int r,int rt){
  if(r<=R&&l>=L){
    return Sum[rt]%mod;
  }
     int m=(l+r)/2;
     PushDowm(rt);   
     ll ans=0;
     if(m>=L){
      ans+=Query(L,R,l,m,rt*2);
      ans=ans%mod;
     }
     if(R>m){
      ans+=Query(L,R,m+1,r,rt*2+1);
      ans=ans%mod;
     }

     return ans;
  
}





int main(){
  //freopen("test/A.in","r",stdin);
  cin>>n>>m;
  for(int i =1;i<=n;++i){
    cin>>a[i];
  }
  
  init();
  bool flag=false;
  
  

  for(int i =0;i<m;++i){
     cin>>op;  // 操作
    if(op==0){
       int L,R;
       ll w;
       cin>>L>>R>>w;
       if(w==1){
         continue;
       }
       while(w>1){
           for(int i = 0;prime[i]<=w;++i){
             if(w%prime[i]==0){
               Update(L,R,prime[i],1,n,1);
               w=w/prime[i];
               break;
             }
           }
       }
    }else{
      if(!flag){
        flag=true;
      }else{
        cout<<endl;
      }
      int L,R;
      cin>>L>>R;
      ll ans=0;
      ans=Query(L,R,1,n,1);
      cout<<ans%mod;
    }
  }

}                 
#include<iostream>
using namespace std;
#define plusn 500005
#define maxn 100005
#define ll long long



ll Add[plusn];   // 懒标记
ll Sum[plusn];   // 求和
ll Mul[plusn];   // 求积懒标记
ll A[maxn];
ll n,M,mod;            
void init(){
    for(int i=0;i<plusn;++i){
        Add[i]=0;
        Sum[i]=0;
        Mul[i]=1;   // 不能初始化为0，不然
        
    }
}

// 更新当前结点的值
void push_up(int rt){
    Sum[rt]=((Sum[rt*2]+Sum[rt*2+1]))%mod;
}
// 构建线段树
// 构建的时候是自下而上，所以只需要push_dowm
void tree_build(int l,int r,int rt){
    if(l==r){
        Sum[rt]=A[l];
        return;
    }
    int m=(l+r)/2;
    tree_build(l,m,rt*2);   // 构建左边
    tree_build(m+1,r,rt*2+1);  // 构建右边
    // 更新当前
    push_up(rt);
}

// 向下传递懒标记
// 是向下传递，所以自己就不用算了
void push_dowm(int rt,ll ln,ll rn){
      // 这个传递不用写add!=0!!!!!!!,不然就有可能传递不下去了
      Sum[rt*2]=(Sum[rt*2]*Mul[rt]%mod+Add[rt]*ln%mod)%mod;
      Sum[rt*2+1]=(Sum[rt*2+1]*Mul[rt]%mod+Add[rt]*rn%mod)%mod;
      // 关键的传递
      Mul[rt*2]=Mul[rt]*Mul[rt*2]%mod;
      Add[rt*2]=(Add[rt*2]*Mul[rt]%mod+Add[rt]%mod)%mod;
      Mul[rt*2+1]=Mul[rt]*Mul[rt*2+1]%mod;
      Add[rt*2+1]=(Add[rt*2+1]*Mul[rt]%mod+Add[rt])%mod;
      Mul[rt]=1;
      Add[rt]=0;

}

// 更新区间的值
void tree_update(int L,int R,int l,int r,ll K, ll C,int rt){
    // 因为有加减的先后问题，所以一定要先传递
    int m=(l+r)/2;

    if(r<=R&&l>=L){
        if(C!=0){   // 加法 
           Add[rt]+=C%mod;
           Sum[rt]=(Sum[rt]+C*(r-l+1)%mod)%mod;
        }else{      // 做乘法
           Mul[rt]=(K*Mul[rt])%mod;
           Add[rt]=(K*Add[rt])%mod;
           Sum[rt]=(Sum[rt]*K)%mod;
        }
        return;
        
    }
    push_dowm(rt,m-l+1,r-m);
    

    // 更新子区间
    if(m>=L){
        tree_update(L,R,l,m,K,C,rt*2);
    }

    if(m+1<=R){
        tree_update(L,R,m+1,r,K,C,rt*2+1);
    }
     // 更新当前节点
     push_up(rt);
}

// 查询
ll tree_query(int L,int R,int l,int r,int rt){
    
    if(r<=R&&l>=L){
        return Sum[rt]%mod;
    }
    int m=(r+l)/2;
    // 向下传递,因为可能没传下去
    // 根节点懒标记不可能存在的，不用担心，因为就是从根节点
    // 更新下去的
    push_dowm(rt,m-l+1,r-m);  // 不传递的话，下面有些地方的值可能没被更新
    ll Ans=0;
    if(m>=L){
        Ans+=tree_query(L,R,l,m,rt*2)%mod;
    }
    if(m+1<=R){
        Ans+=tree_query(L,R,m+1,r,rt*2+1)%mod;
    }
    return Ans%mod;

}

int main(){
    //freopen("test/B.in","r",stdin);
    init();
    scanf("%lld%lld%lld",&n,&M,&mod);
    for(int i = 1;i<=n;++i){
        scanf("%lld",&A[i]);
    }
    // for(int i =1;i<=n;++i){
    //     cout<<A[i]<<" ";
    // }
    // cout<<endl; 
    tree_build(1,n,1);
    //  for(int i = 1;i<=9;++i){
    //      cout<<i<<" "<<Sum[i]<<endl;
    //  }
    ll opt,x,y,c,k;
    for(int i =0;i<M;++i){
       scanf("%lld",&opt);
       if(opt==1){
            scanf("%lld%lld%lld",&x,&y,&k);
            
             tree_update(x,y,1,n,k,0,1);
       }else if(opt==2){
           scanf("%lld%lld%lld",&x,&y,&c);
           tree_update(x,y,1,n,1,c,1);
       }else{
           scanf("%lld%lld",&x,&y);
           printf("%lld\n",(tree_query(x,y,1,n,1)));
       }
    //    cout<<"***** "<<endl;
    //     for(int i = 1;i<=9;++i){
    //      cout<<i<<" "<<Sum[i]<<endl;
    //     }
    }
    // for(int i = 1;i<=5;++i){
    //     for(int j = 1;j<=5;++j){
    //         cout<<i<<" "<<j<<" "<<tree_query(i,j,1,n,1)<<endl;
    //     }
    // }


}
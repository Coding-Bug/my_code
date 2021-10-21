#include<iostream>
using namespace std;
#define plusn 400005
#define maxn 100005
#define ll long long
ll Add[plusn];   // 懒标记
ll Sum[plusn];   // 求和
ll A[maxn];
ll n,m;            
void init(){
    for(int i=0;i<plusn;++i){
        Add[i]=0;
        Sum[i]=0;
    }
}

// 更新当前结点的值
void push_up(int rt){
    Sum[rt]=Sum[rt*2]+Sum[rt*2+1];

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
void push_dowm(int rt,int ln,int rn){
    if(Add[rt]!=0){
        // 先传递下去
        Add[rt*2]+=Add[rt];   // 是+=,因为下面可能本来就还有标记
        Add[rt*2+1]+=Add[rt];
        // 计算下面的值
        Sum[rt*2]+=Add[rt]*ln;
        Sum[rt*2+1]+=Add[rt]*rn;
        // 清除懒标记
        Add[rt]=0;
    }

}

// 更新区间的值
void tree_update(int L,int R,int l,int r,ll C,int rt){
    if(r<=R&&l>=L){
        Add[rt]+=C;
        Sum[rt]+=C*(r-l+1);
        return;
    }
    int m=(l+r)/2;
    // 向下传递懒标记
    // 因为后面要计算子区间了，可能子区间之前有的懒标记没传递下去
    push_dowm(rt,m-l+1,r-m);
    // 更新子区间
    if(m>=L){
        tree_update(L,R,l,m,C,rt*2);
    }

    if(m+1<=R){
        tree_update(L,R,m+1,r,C,rt*2+1);
    }
     // 更新当前节点
     push_up(rt);
}

// 查询
ll tree_query(int L,int R,int l,int r,int rt){
    if(r<=R&&l>=L){
        return Sum[rt];
    }
    int m=(r+l)/2;
    // 向下传递,因为可能没传下去
    // 根节点懒标记不可能存在的，不用担心，因为就是从根节点
    // 更新下去的
    push_dowm(rt,m-l+1,r-m);  // 不传递的话，下面有些地方的值可能没被更新
    ll Ans=0;
    if(m>=L){
        Ans+=tree_query(L,R,l,m,rt*2);
    }
    if(m+1<=R){
        Ans+=tree_query(L,R,m+1,r,rt*2+1);
    }
    return Ans;

}

int main(){
    freopen("test/A.in","r",stdin);
    init();
    scanf("%lld%lld",&n,&m);
    for(int i = 1;i<=n;++i){
        scanf("%lld",&A[i]);
    }
    tree_build(1,n,1);
    //  for(int i = 1;i<=9;++i){
    //      cout<<Sum[i]<<endl;
    //  }
    ll opt,x,y,k;
    for(int i =0;i<m;++i){
       scanf("%lld",&opt);
       if(opt==1){
           scanf("%lld%lld%lld",&x,&y,&k);
           tree_update(x,y,1,n,k,1);
       }else{
           scanf("%lld%lld",&x,&y);
           printf("%lld\n",tree_query(x,y,1,n,1));
       }
    }


}
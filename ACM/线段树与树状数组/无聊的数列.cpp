#include<iostream>
using namespace std;
#define maxn 500005
#define ll long long
ll Sum[maxn];
ll lazy_K[maxn];  // 首项懒标记
ll lazy_D[maxn];  // 公差懒标记
int a[maxn];


void init(){
    for(int i = 0;i<maxn;++i){
        Sum[i]=0;
        lazy_D[i]=0;
        lazy_K[i]=0;
    }
}
void push_up(int rt){
    Sum[rt]=Sum[rt*2]+Sum[rt*2+1];
}


void tree_init(int l,int r,int rt){
    if(l==r){
        Sum[rt]=a[l];
        return;
    }
    int m=(l+r)/2;
    tree_init(l,m,rt*2);
    tree_init(m+1,r,rt*2+1);
    push_up(rt);
}


void push_dowm(int rt,int ln,int rn){
    // 左节点的懒标记直接传
     lazy_K[rt*2]+=lazy_K[rt];
     lazy_D[rt*2]+=lazy_D[rt];
    // 右边注意一下首项
    lazy_K[rt*2+1]+=lazy_K[rt]+(ln)*lazy_D[rt];
    lazy_D[rt*2+1]+=lazy_D[rt];


    // 计算
    Sum[rt*2]+=ln*lazy_K[rt]+(ln*(ln-1)*lazy_D[rt])/2;
    Sum[rt*2+1]+=(lazy_K[rt]+(ln)*lazy_D[rt])*rn+(rn*(rn-1)*lazy_D[rt])/2;
    lazy_D[rt]=0;
    lazy_K[rt]=0;
}


void tree_update(int L,int R,int l,int r,ll K,ll D,int rt){
    //cout<<Sum[rt]<<" "<<rt<<" "<<len<<" "<<K<<" "<<D<<endl;
    
    if(r<=R&&l>=L){
        K=K+(l-L)*D;
        lazy_D[rt]+=D;
        lazy_K[rt]+=K;
        int len=r-l+1;
        //cout<<Sum[rt]<<" "<<rt<<" "<<len<<" "<<K<<" "<<D<<endl;
        Sum[rt]+=K*len+(len*(len-1)*D)/2;
        
        return;
    }

    int m=(r+l)/2;
    push_dowm(rt,m-l+1,r-m);
    if(m>=L){
        tree_update(L,R,l,m,K,D,rt*2);
    }
    if(m+1<=R){
        // 注意这里是K+D*(m-L+1)而不是K+D*(m-l+1)
        // 并且是m大于等于l的情况
        
        tree_update(L,R,m+1,r,K,D,rt*2+1);
    }
    push_up(rt);
}

ll tree_query(int L,int R,int l,int r,int rt){
    if(l>=L&&r<=R){
        return Sum[rt];
    }
    int m=(r+l)/2;
    push_dowm(rt,m-l+1,r-m);
    ll Ans=0;
    if(m>=L){
        Ans+=tree_query(L,R,l,m,rt*2);
    }
    if(m+1<=R){
        Ans+=tree_query(L,R,m+1,r,rt*2+1);
    }
    return Ans;


}
int n,m;



int main(){
    init();
    //freopen("test/C.in","r",stdin);
    //cin>>n>>m;
    scanf("%d%d",&n,&m);
    // 先构建
    for(int i=1;i<=n;++i){
        //cin>>temp;
        scanf("%d",&a[i]);
    }
    tree_init(1,n,1);
    
    int opt,l,r;
    ll k,D;
    int p;
    for(int i = 0;i<m;++i){
        //cin>>opt;
        scanf("%d",&opt);
        if(opt==1){
           //cin>>l>>r>>k>>D;
           scanf("%d%d%lld%lld",&l,&r,&k,&D);
           tree_update(l,r,1,n,k,D,1);
           //cout<<l<<r<<k<<D<<endl;
        //    for(int i = 1;i<=9;++i){
        //       cout<<i<<" "<<Sum[i]<<endl ;
        //    }
        //    cout<<endl;
        }else{
            //cin>>p;
            scanf("%d",&p);
            printf("%lld\n",tree_query(p,p,1,n,1));  
        }
    }

    
}
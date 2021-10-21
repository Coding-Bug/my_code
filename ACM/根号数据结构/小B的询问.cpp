#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define maxn 50005
typedef struct{
    int l;
    int r;
    int pos;
}Q;

inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return x*f;
}
Q query[maxn];   // 询问数组
int n=0;
int m=0;
int k=0;
int a[maxn]={0};
int block; 
int belong[maxn]={0};
int ans[maxn]={0};
int has[maxn]={0};
int ret=0; // 目前的答案
int L=1;   // 上一次的左区间
int R=0;


bool cmp(Q a,Q b){
    if(belong[a.l]!=belong[b.l]){
        return a.l<b.l;
    }else{
        return a.r<b.r;
    }
}


inline void Add(int x){
    //cout<<x<<"  "<<ret<<" "<<has[x]<<" "<<endl;
     ret-=has[x]*has[x];
     ++has[x];
     ret+=has[x]*has[x];
}

inline void del(int x){
    ret-=has[x]*has[x];
     --has[x];
     ret+=has[x]*has[x];
}
int main(){
    //freopen("test/B.in","r",stdin);
    //cin>>n>>m>>k;
    //scanf("%d%d%d",&n,&m,&k);
    n=read();
    m=read();
    k=read();
    block= sqrt(n);
    for(int i =1;i<=n;++i){
        //cin>>a[i];
        //scanf("%d",&a[i]);
        a[i]=read();
        belong[i]=(i-1)/block+1;   // 是belong i
    }

    for(int  i =1;i<=m;++i){
        //cin>>query[i].l>>query[i].r;
        //scanf("%d%d",&query[i].l,&query[i].r);
        query[i].l=read();
        query[i].r=read();
        query[i].pos=i;
    }
    sort(query+1,query+1+m,cmp);
    // for(int i = 1;i<=4;++i){
    //     cout<<query[i].l<<" "<<query[i].r<<endl;
    // }
    // exit(1);
    //cout<<"hh"<<endl;
    for(int i = 1;i<=m;++i){
        //cout<<"hh"<<endl;
        int l,r,pos;
        l=query[i].l;
        r=query[i].r;
        pos=query[i].pos;
        while(R<r) Add(a[++R]);
        while(L>l) Add(a[--L]);
        while(R>r) del(a[R--]);
        while(L<l) del(a[L++]);
        ans[pos]=ret;
    }
    for(int i = 1;i<=m;++i){
        //cout<<ans[i]<<endl;
        printf("%d\n",ans[i]);
    }
}

#include<iostream>
#include<algorithm>
#include<cmath>
#define ll long long
using namespace std;
#define maxn 100004

typedef struct{
    int l;
    int r;
    int pos;
}Q;
Q  query[maxn];
ll a[maxn]={0};
ll ans[maxn]={0};
ll belong[maxn];
ll has[maxn]={0};    // h[i]是前缀和为i的点有多少
ll ret;          // 当前区间有多少对
ll n,m,k;
ll block;
ll L=0;
ll R=1;
bool cmp(Q a,Q b){
      if(belong[a.l]==belong[b.l]){
          return a.r<b.r;
      }else{
          return a.l<b.l;
      }
}
void add(int x){
    ret-=has[x]*has[x^k];    // 前缀和为x的贡献，反过来也是对称的
    has[x]++;
    ret+=has[x]*has[x^k];
};

void del(int x){
    ret-=has[x]*has[x^k];
    --has[x];
    ret+=has[x]*has[x^k];
};
int main(){
    freopen("test/A.in","r",stdin);
    cin>>n>>m>>k;
    block=sqrt(n);
    cin>>a[1];
    for(int i = 2;i<=n;++i){
        cin>>a[i];
        a[i]=a[i]^a[i-1];    // 求异或的前缀和
        belong[i]=(i-1)/block+1;
    }
    for(int i=1;i<=m;++i){
        cin>>query[i].l>>query[i].r;
        query[i].pos=i;
    }
    sort(query+1,query+1+m,cmp);
    for(int i = 1;i<=m;++i){
        int l=query[i].l;
        int r=query[i].r;
        int pos=query[i].pos;
        while(R<r) add(a[++R]);
        while(L>l) add(a[--L]);
        while(R>r) del(a[R--]);
        while(L<l) del(a[L++]);
        ans[pos]=ret;
    }

    for(int i = 0;i<=m;++i){
        cout<<ans[i]<<endl;
    }
}
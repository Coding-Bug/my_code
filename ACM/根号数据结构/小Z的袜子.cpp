#include<iostream>
using namespace std;
#include<cmath>
#include<algorithm>
#define maxn 50004

typedef struct{
    int l;
    int r;
    int pos;
}Q;
typedef struct Ans
{
    int a1;
    int a2;
}Ans;

Q query[maxn];
int belong[maxn];
Ans ans[maxn];
int a[maxn];
int block=0;     // 块大小
int has[maxn];   // 记录这种袜子有多少只
int num[maxn];   // 记录这种袜子有多少相同的
int ret=0;         // 一共多少对
int retn=0;        // 一共多少只
int sam=0;         // 一共多少对相同的
int L=1;
int R=0;
int n,m;

bool cmp(Q a,Q b){
      if(belong[a.l]==belong[b.l]){
          return a.r<b.r;
      }else{
          return a.l<b.l;
      }
}

void add(int x){
     sam-=num[x];
     num[x]+=has[x];
     has[x]++;
     sam+=num[x];
     ret+=retn;
     retn++;
}
void del(int x){
     sam-=num[x];
     has[x]--;
     num[x]-=has[x];
     sam+=num[x];
     retn--;
     ret-=retn;
}

int gcd(int x,int y){
    if(x%y==0){
        return y;
    }
    return gcd(y,x%y);
}

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    block=sqrt(n);
    for(int i = 1;i<=n;++i){
        cin>>a[i];
        belong[i]=(i-1)/block+1;
    }

    for(int i =1;i<=m;++i){
        cin>>query[i].l>>query[i].r;
        query[i].pos=i;
    }

    sort(query+1,query+1+m,cmp);
    for(int i=1;i<=m;++i){
        int l=query[i].l;
        int r=query[i].r;
        int pos=query[i].pos;
        while(R<r) add(a[++R]);
        while(L>l) add(a[--L]);
        while(R>r) del(a[R--]);
        while(L<l) del(a[L++]);
        if(l==r||sam==0){
            ans[pos].a1=0;
            ans[pos].a2=1;
        }else{
            int ans1=sam;
            int ans2=ret;
            int g=gcd(ans1,ans2);
            while(g!=1){
                ans1/=g;
                ans2/=g;
                g=gcd(ans1,ans2);
            }
            ans[pos].a1=ans1;
            ans[pos].a2=ans2;
        }
    }
    for(int i = 1;i<=m;++i){
        cout<<ans[i].a1<<'/'<<ans[i].a2<<endl;
    }
}
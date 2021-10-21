#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define maxn 100005

typedef struct 
{
    int l;
    int r;
    int pos;
}Q;
Q query[maxn];
int belong[maxn]={0};
int a[maxn];
int block;   // 区数
bool ans[maxn];
int has[maxn]; // 桶
int ret=0;   // 区间中数的总数
int L=1;
int R=0; 
int n,q;
bool cmp(Q a,Q b){
     if(belong[a.l]==belong[b.l]){
         return a.r<b.r;
     }else{
         return a.l<b.l;
     }
}

void add(int x){  // 加上这个数
     if(has[x]==0){  // 本来没有这种数
         ret++;    
     }
     has[x]++;
}

void del(int x){
    has[x]--;
    if(has[x]==0){
        ret--;
    }
}

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>q;
    block=sqrt(n);
    for(int i =1;i<=n;++i){
       cin>>a[i];
       belong[i]=(i-1)/block+1;
    }

    for(int i = 1;i<=q;++i){
        cin>>query[i].l>>query[i].r;
        query[i].pos=i;
    }
    // 按块排队
    sort(query+1,query+1+q,cmp);
    for(int i = 1;i<=q;++i){
        int l=query[i].l;
        int r=query[i].r;
        int pos=query[i].pos;
        while(R<r) add(a[++R]);
        while(L>l) add(a[--L]);
        while(R>r) del(a[R--]);
        while(L<l) del(a[L++]);
        if(ret==r-l+1){
            ans[pos]=true;
        }else{
            ans[pos]=false;
        }
    }
    for(int i = 1;i<=q;++i){
        if(ans[i]){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }

}
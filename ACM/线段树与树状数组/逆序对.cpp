#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 500005
int a[maxn];
int b[maxn];
int c[maxn];
int t[maxn];    // 这个区间中的数出现了多少个几次，也就是树状的那个数组
int n=0;
long long ans=0;

void init(){
    for(int i = 0;i<maxn;++i){
        a[i]=0;
        t[i]=0;
    }
}
// 树状数组是1在前面，n在后面。
// 所以所以让最大为1，最小排n，这样就可以往前搜比他大的出现了多少次了
bool cmp(int a,int b){
    return a<b;
}

// 获取最小的那个位数
int lowbit(int x){
    return x&(-x);
}

// 更新值
// x是更新位置，l是最大下标
void update(int x,int l){
     // 包含x的结点是一直加2^lowbit
     for(int i =x;i<=l;i+=lowbit(i)){
         t[i]++;
     }
}

// 也就是求sum[1-x]
void query(int x){
    for(int i=x;i>0;i-=lowbit(i)){
        ans+=t[i];
    }
}


int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&n);
    for(int i = 0;i<n;++i){
        //cin>>a[i];
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b,b+n,cmp);
    int l=unique(b,b+n)-b;   // 去重后的长度
    // for(int i =0;i<l;++i){
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
    // for(int i =0;i<l;++i){
    //     cout<<b[i]<<" ";
    // }
    //  cout<<endl;
    // 获取离散化数组c，下标1-n
    
    for(int i = 0;i<n;++i){
        c[i]=lower_bound(b,b+l,a[i])-b+1;
    }


    // for(int i =0;i<n;++i){
    //     cout<<c[i]<<" ";
    // }
    // cout<<endl;
    // 构建数组
    // 要从后面插入，因为只能查询比他小的
    for(int i=n-1;i>=0;--i){
        //cout<<i<<endl;
        update(c[i],l);
        query(c[i]-1);   // 查询比他小的出现了多少个 
    }
    //cout<<ans<<endl;   // 输出
    printf("%lld\n",ans);

    








}
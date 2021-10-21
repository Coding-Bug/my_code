#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define maxn 200004
typedef struct{
    ll w;
    ll v;
}Node;
typedef struct 
{
    int l;
    int r;
}Query;

Query q[maxn];
Node a[maxn];
ll sumv[maxn];
ll sumi[maxn];

int n,m;
ll s;

ll cal(ll W){

    // 预处理出前缀和
    for(int i = 1;i<=n;++i){
        if(a[i].w>=W){
            sumv[i]=sumv[i-1]+a[i].v;
            sumi[i]=sumi[i-1]+1;
        }else{
            sumv[i]=sumv[i-1];
            sumi[i]=sumi[i-1];
        }
    }
    
    ll ans=0;
    for(int i =1;i<=m;++i){
        int l=q[i].l;
        int r=q[i].r;
        ll temp=(sumi[r]-sumi[l-1])*(sumv[r]-sumv[l-1]);
        ans+=temp;
    }
    return ans;
   
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m>>s;
    for(int i = 1;i<=n;++i){
        cin>>a[i].w>>a[i].v;
    }
    // for(int i =1;i<=n;++i){
    //     cout<<a[i].w<<" "<<a[i].v<<" "<<sumv[i]<<endl;
    // }
    for(int i = 1;i<=m;++i){
        cin>>q[i].l>>q[i].r;
    }
    ll l=0;
    ll r=1e10;
    ll W;
    ll ansy;
    while(l<r){
        //cout<<l<<" "<<r<<endl;
        if(l==r-1){
            ll ans1=0;
            ll ans2=0;
            ans1=cal(l);
            ans2=cal(r);
            ansy= ((abs(s-ans1))>(abs(s-ans2))?ans2:ans1);
            break;
        }
        W=(l+r)/2;
        ansy=cal(W);
        if(ansy>s){
            l=W;
        }else{
            r=W;
        }
        
    }
    cout<<abs(s-ansy)<<endl;
}
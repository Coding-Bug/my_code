#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define maxn 10005

int T;
int n,m;
ll a[maxn];
ll b[maxn];
bool cmp(ll a,ll b){
    return a>b;
}
bool judge(){
    for(int i = 1;i<=n;++i){
        bool flag=false;
        for(int j =1;j<=m;++j){
            if(a[i]<=b[j]){
                b[j]-=a[i];
                flag=true;
                break;
            }
        }
        if(!flag){
            //cout<<i<<" "<<a[i]<<" "<<b[i]<<endl;
            return false;
        }
    }
    return true;

}
int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&T);
    while(T--){
         scanf("%d%d",&n,&m);
         for(int i =1;i<=n;++i){
             scanf("%lld",&a[i]);
         }
         for(int i =1;i<=m;++i){
             scanf("%lld",&b[i]);
         }
         sort(a+1,a+1+n,cmp);
         sort(b+1,b+1+m,cmp);
         if(judge()){
             printf("Yes\n");
         }else{
             printf("No\n");
         }
    }

}
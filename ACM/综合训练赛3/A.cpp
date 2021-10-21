#include<iostream>
using namespace std;
#define ll long long 
#define maxn 100005
const ll INF=1e18;
typedef struct{
    ll a;
    ll b;
}Node;
Node node[maxn];
ll Q[maxn];
int head=0;
int tail=0;
ll n,m;
int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%lld%lld",&n,&m);

    for(int i = 1;i<=n;++i){
       scanf("%lld%lld",&node[i].a,&node[i].b);
    }
    int i=1;
    int j=1;
    ll sum=0;   // 记录a的和
    ll ans=1e18+2;
    for( j =1;j<=n;++j){
        sum+=node[j].a;
        // 维持单调
        while(head>tail&&node[j].b>Q[head-1]){
            head--;
        }
        Q[head++]=node[j].b;
        while(true){
            if(sum-node[i].a>=m){
                //cout<<i<<endl;
                sum-=node[i].a;
                if(Q[tail]==node[i].b){ 
                    tail++;
                    if(Q[tail]<ans){
                     //cout<<Q[tail]<<endl;
                     ans=Q[tail];
                    }
                    
                }
                i++;
            }else{
                break;
            }
        }
        if(Q[tail]<ans&&sum>=m){
            //cout<<Q[tail]<<endl;
            ans=Q[tail];
        }
        
    }
    cout<<ans<<endl;



}
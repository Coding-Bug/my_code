#include<iostream>
using namespace std;
#define maxn 81
int t,n;
long long ans=0;
bool vis[maxn];
void dfs(int i,int now){
     if(i==n){
         ans++;
         return;
     }
     //cout<<i<<" "<<now<<endl;
     int next;
     next=now+i;
     if(next>n){
         next-=n;
     }
     if(!vis[next]){
         vis[next]=true;
         dfs(i+1,next);
         vis[next]=false;
     }
     next=now-i;
     if(next<=0){
        next+=n;
     }
     if(!vis[next]){
             vis[next]=true;
             dfs(i+1,next);
             vis[next]=false;
     }
}
int main(){
    freopen("test/A.in","r",stdin);
    scanf("%d",&t);
    while(t--){
        //cout<<"**************"<<endl;
        scanf("%d",&n);
        ans=0;
        
        for(int i = 0;i<maxn;++i){
            vis[i]=false;
        }
        vis[1]=true;
        dfs(1,1);
        printf("%d\n",ans);
    }
}
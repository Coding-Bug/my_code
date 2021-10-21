#include<iostream>
using namespace std;
#define maxn 1003
int f[maxn];

int find(int x){
    if(f[x]==x){
        return f[x];
    }
    f[x]=find(f[x]);
    return f[x];
}

void Union(int x,int y){
     if(f[x]==f[y]){
         return;
     }

     f[find(x)]=find(y);    // 根部相连
}
int n,m;

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    while(n!=0){
        cin>>m;
        int ans=0;
        int k=0;
        for(int i = 0;i<=n;++i){
           f[i]=i;
        }

        for(int i = 0;i<m;++i){
            int u,v;
            cin>>u>>v;
            Union(u,v);
        }

        for(int i = 1;i<=n;++i){
            find(i);
        }

        for(int j = 1;j<=n;++j){
           if(f[j]==j){
             k++;
            }
        }

        ans=k-1;
        cout<<ans<<endl;
        cin>>n;
    }


}
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 2004
int f[maxn];
int n,m;
int find(int x){
    if(f[x]==x){
        return x;
    }
    f[x]=find(f[x]);
    return f[x];
}

void Union(int x,int y){
     if(f[x]==f[y]){
         return;
     }
     f[find(x)]=find(y);
}
int main(){
    //freopen("test/A.in","r",stdin);
    for(int i =0;i<=maxn;++i){
        f[i]=i;
    }
    cin>>n>>m;
    char c;
    int x,y;
    for(int i=0;i<m;++i){
        cin>>c;
        cin>>x>>y;
        if(c=='F'){
           Union(x,y);
        }else{        // 如果是敌人，则分别与其扩展位连接
           Union(x,y+n);
           Union(x+n,y);
        }
    }

    for(int i = 1;i<=2*n;++i){
        find(i);
    }
    int ans=1;
    // 因为有了反集，所以判断是否一个团体的时候就不能偷懒了
    
    sort(f,f+n+1);
    
    for(int i =2;i<=n;++i){
        if(f[i]!=f[i-1]){
            ans++;
        }
    }
    cout<<ans<<endl;
}
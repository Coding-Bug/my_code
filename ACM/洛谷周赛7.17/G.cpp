#include <bits/stdc++.h>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0)
int K,N,M;
int acm[105];
int a[1007][1007]={0};
bool visit[1007];
int sum[1007]={0};
int ans=0;

// r存放前一个
void dfs(int i){
    for(int j = 1;j<=N;++j){
       if(!visit[j]&&a[i][j]==1){
           visit[j]=true;
           sum[j]++;
           dfs(j);
       }
    }
}

int main(){ 
    TLE;
    //freopen("test/G.txt","r",stdin);
    cin>>K>>N>>M;
    for(int i =1;i<=K;++i){
          cin>>acm[i];
    }

    for(int i = 1;i<=N;++i){
        for(int j = 1;j<=N;++j){
           a[i][j]=0;
        }
        a[i][i]=1;
    }
    
    int x,y;
    for(int i = 1;i<=M;++i){
        cin>>x>>y;
        a[x][y]=1;
    }

    
    for(int i = 1;i<=K;++i){
        for(int j = 1;j<=N;++j){
            visit[j]=false;
        }
        sum[acm[i]]++;
        visit[acm[i]]=true;
        dfs(acm[i]); 
    }

    for(int i = 1;i<=N;++i){
        if(sum[i]==K){
            ans++;
        }
    }
  
    cout<<ans<<endl;

}
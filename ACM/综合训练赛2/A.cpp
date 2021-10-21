#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 40
int t;
int n,m;
typedef struct{
     int x;
     int y;
     int w;
}Node;
bool cmp(Node a,Node b){
    return a.w>b.w;
}
Node a[maxn];
bool vis[8][8];
int ans=0;
int cnt=0;
int mrk[maxn][maxn];
int mov[8][2]={{0,1},{1,1},{-1,1},{0,-1},{1,-1},{-1,-1},{1,0},{-1,0}};
void judge(int k){
     int x=a[k].x;
     int y=a[k].y;
     for(int e=0;e<8;++e){
         int nx=x+mov[e][0];
         int ny=y+mov[e][1];
         if(nx>=0&&nx<n&&ny>=0&&ny<m){
             if(!vis[nx][ny]){
                 vis[nx][ny]=true;
                 mrk[nx][ny]=k;
             }
         }
     }
}
void rejudge(int k){
     int x=a[k].x;
     int y=a[k].y;
     for(int e=0;e<8;++e){
         int nx=x+mov[e][0];
         int ny=y+mov[e][1];
         if(nx>=0&&nx<n&&ny>=0&&ny<m){
             if(vis[nx][ny]&&mrk[nx][ny]==k){
                 vis[nx][ny]=false;
             }
         }
     }
}

bool judgemin(int k,int now){
    int temp=now;
    for(int i =k;i<cnt;++i){
        if(!vis[a[i].x][a[i].y]){
           temp+=a[i].w;
        }
    }
    if(temp<ans){
        return false;
    }
    return true;
}



void dfs(int x,int now){
     if(now>ans){
         //cout<<x<<endl;
         ans=now;
     }
     for(int i = x;i<cnt;++i){
         Node p=a[i];
         // 如果已经有过
         if(vis[p.x][p.y]){
             continue;
         }
         if(!judgemin(i,now)){
             continue;
         }

         vis[p.x][p.y]=true;
         judge(i);
         dfs(i,now+a[i].w);
         vis[p.x][p.y]=false;
         rejudge(i);
     }
     
}




int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        ans=0;
        cnt=0;
        for(int i =0;i<maxn;++i){
            for(int j = 0;j<maxn;++j){
                vis[i][j]=false;
                mrk[i][j]=-1;
            }
        }
        cin>>n>>m;
        for(int i = 0;i<n;++i){
            for(int j = 0;j<m;++j){
                a[cnt].x=i;
                a[cnt].y=j;
                cin>>a[cnt].w;
                cnt++;
            }
        }
        //sort(a,a+cnt,cmp);
        dfs(0,0);
        cout<<ans<<endl;
    }
}
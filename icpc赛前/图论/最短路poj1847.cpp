#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 210
#define INF 1000000000
int N,A,B;

// 前向星
// 注意边数的最大值不是点数的最大值！！！！
// 所以开最大值的时候开点的两倍
int head[maxn];
int to[maxn];
int nex[maxn];
int w[maxn];
int cnt=0;
void add_edge(int u,int v,int W){
    to[cnt]=v;
    w[cnt]=W;
    nex[cnt]=head[u];
    head[u]=cnt++;   
    
}
int dis[maxn];
bool vis[maxn];
// 权值从小到大
struct cmp
{
    bool const operator ()(int a,int b)const {
        return dis[a]>dis[b];
    }
};
void init(){
    // 注意memset有坑，所以用循环
    for(int i = 0;i<maxn;++i){
        dis[i]=INF;
        head[i]=-1;
        vis[i]=false;
    }
}
void dijstra(int beg){
    dis[beg]=0;
    priority_queue<int ,vector<int>,cmp> Q;
    Q.push(beg);
    while(!Q.empty()){
        int q=Q.top();
        Q.pop();
        if(vis[q]){
            continue;
        }
        vis[q]=true;
        for(int i = head[q];i!=-1;i=nex[i]){
            int v=to[i];
            if(!vis[v]&&dis[v]>dis[q]+w[i]){
                dis[v]=dis[q]+w[i];   
            }
            Q.push(v);
        }
    }
}


int main(){
    //freopen("test/A.in","r",stdin);
    cin>>N>>A>>B;
    init();
    for(int i = 1;i<=N;++i){
        int k = 0;
        cin>>k;
        int to;
        for(int j = 0;j<k;++j){
            cin>>to;
            if(j==0){
                add_edge(i,to,0);
            }else{
                add_edge(i,to,1);
            }
        }
    }
    
    dijstra(A);
    if(dis[B]==INF){
        cout<<"-1"<<endl;
    }else{
        cout<<dis[B]<<endl;
    }
}
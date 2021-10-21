#include<iostream>
using namespace std;
#include<queue>
#define maxn 45000

typedef struct{
    int to;
    int next;
}Edge;
Edge edge[maxn];
int head[maxn];
int cnt=0;
typedef struct{
    int in=0;
    int out=0;   
}Node;
Node node[maxn];
bool vis[maxn];
int n,m;
void add_edge(int u, int v){
     edge[cnt].to=v;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}
void init(){
    for(int i = 0;i<maxn;++i){
        head[i]=-1;
    }
}


void fun(int u){
    queue<int> Q;
    Q.push(u);
    vis[u]=true;
    while(!Q.empty()){
        int k=Q.front();
        Q.pop();
        Node p=node[k];
        for(int i =head[k];i!=-1;i=edge[i].next){
            int to=edge[i].to;
            if(vis[to]){
                continue;
            }

            node[u].out++;
            node[to].in++;
            vis[to]=true;
            Q.push(to);
        }
    }

} 

int main(){
    //freopen("test/A.in","r",stdin);
    init();
    scanf("%d%d",&n,&m);
    for(int i = 0;i<m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
    }
    for(int i =1;i<=n;++i){
        for(int j =1;j<=n;++j){
            vis[j]=false;
        }
        fun(i);
    }
    int ans=0;
    for(int i=1;i<=n;++i){
        if(node[i].in+1+node[i].out==n){
           ans++;
        }
    }
    printf("%d\n",ans);

}
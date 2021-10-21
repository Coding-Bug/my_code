#include<iostream>
#include<queue>
using namespace std;
#define maxn 100005
#define maxm 200005
typedef struct Edge
{
    int to;
    int w=1;
    int next;
}Edge;

typedef struct  Node
{
    bool flag=false;  // 是不是单个节点或者开始结点
    int ans=0;
    int pos;
    int in=0;  // 入度
}Node;
Node node[maxn];

Edge edge[maxm];

int head[maxn];
int cnt=0;
void add_edge(int u,int v){
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
int n,m;
int ans=0;

void fun(){
     queue<Node> Q;
     // 入度为0的结点入栈
     for(int i=0;i<n;++i){
         if(node[i].in==0){
             node[i].ans=1;
             node[i].flag=true;
             Q.push(node[i]);
         }
     }
     while(!Q.empty()){
         Node p=Q.front();
         Q.pop();
         int ans=p.ans;
         int u=p.pos;
         for(int i = head[u];i!=-1;i=edge[i].next){
             int to =edge[i].to;
             node[to].in--;
             node[to].ans+=node[u].ans;
             if(node[to].in==0){
                 Q.push(node[to]);
             }      
         }
     }



}
int main(){
    
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    for(int i = 0;i<n;++i){
        node[i].pos=i;
        head[i]=-1;
    }
    for(int i =0 ;i<m;++i){
       int u,v;
       cin>>u>>v;
       u--;
       v--;
       add_edge(u,v);
       node[v].in++;
    }
    fun();
    for(int i = 0;i<n;++i){
        if(head[i]==-1&&!node[i].flag){
            ans+=node[i].ans;
        }
    }
    cout<<ans<<endl;

}
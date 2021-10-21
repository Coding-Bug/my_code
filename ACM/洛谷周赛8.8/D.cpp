#include<iostream>
#include<queue>
using namespace std;
#define maxn 65535
#define maxm 1000005
typedef struct{
    int to;
    int next;
    
    
}Edge;
typedef struct Node{
    int in=0;
    int out=0;
    int w=0;
    int pos;
    bool operator <(const Node &a) const{
        return in>a.in;
    }
}Node;
Node node[maxn];
Edge edge[maxm];


int cnt=0;
int head[maxn];
int n=0;
int ans=0;
void add_edge(int u,int v){
    edge[cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void init(){
    for(int i=0;i<maxn;++i){
        head[i]=-1;
        node[i].pos=i;
    }
}

void findans(){
    queue<Node>  Q;
    for(int i = 1;i<=n;++i){
        if(node[i].in==0){
          Q.push(node[i]);
        }
    }

    while(!Q.empty()){
        
       Node p;
       p=Q.front();
       Q.pop();
       for(int i = head[p.pos];i!=-1;i=edge[i].next){ 
           int to=edge[i].to;
           //cout<<i<<" "<<to<<endl;
           node[to].in--;
           
           if(node[i].out==1){
               node[to].w+=p.w+1;
           }
           node[i].out--;
           if(node[to].in==0){
               Q.push(node[to]);
           }
       }
    }

}

int main(){
    init();
    freopen("test/A.in","r",stdin);
    scanf("%d",&n);
    int next=0;
    for(int i = 1;i<=n;++i){
        scanf("%d",&next);
        while(next!=0){
            add_edge(i,next);
            node[next].in++;
            node[i].out++;
            scanf("%d",&next);
        }
    }
    //cout<<edge[0].to<<endl;
    // for(int i = 1;i<=n;++i){
    //     cout<<node[i].in<<endl;
    // }
    
    findans();
    for(int i=1;i<=n;++i){
        cout<<i<<" "<<node[i].w<<endl;
    }
    for(int i = 1;i<=n;++i){
        printf("%d\n",node[i].w);
    }
    
}
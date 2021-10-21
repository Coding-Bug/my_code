#include<iostream>
using namespace std;
#define maxn 1000004
#define maxm 1000005
#define maxb  50

typedef struct 
{
    int to;
    int next;
}Edge;

int head[maxn];
Edge edge[maxn];
int fa[maxn][maxb];   // fa[1][1]表示第一个结点的2^1个父亲
int dep[maxn];        // 每个点的深度

int n,m,s;   // 结点数，询问个数，根结点序号
int cnt=0;
void add_edge(int u,int v){
     edge[cnt].to=v;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}
void init(){
    for(int i = 0;i<maxn;++i){
        head[i]=-1;
        dep[i]=-1;
    }
    for(int i=0;i<maxn;++i){
        for(int j = 0;j<maxb;++j){
            fa[i][j]=0;
        }
    }
}

// 记录关系
void init_fat(int son,int fad){
    fa[son][0]=fad;
    dep[son]=dep[fad]+1;
    for(int i = 1;i<maxb;++i){
       fa[son][i]=fa[fa[son][i-1]][i-1];
    }
    // 对son的孩子建立关系
    for(int i=head[son];i!=-1;i=edge[i].next){
        if(edge[i].to!=fad){  // 不能反向建边
          init_fat(edge[i].to,son);
        }
    }
}

// 找公共祖先
// 默认x深
int find(int x,int y){
    // 找深的做x
    if(dep[x]<dep[y]){
        swap(x,y);
    }
   // 二进制的魅力，循环一遍一定能把一个数走完 
    for(int i=maxb-1;i>=0;--i){
        if(dep[fa[x][i]]>=dep[y]){
            x=fa[x][i];
        }
    }
    //cout<<x<<" "<<y<<endl;
    // 如果这就想同乐，直接返回
    if(x==y){
        return x;
    }

    // 找到最深的不同的结点
    for(int i=maxb-1;i>=0;--i){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    
    return fa[x][0];
}


int main(){
    //freopen("test/A.in","r",stdin);
    init();
    cin>>n>>m>>s;
    for(int i = 0;i<n-1;++i){
        int u,v;
        cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);   // 要建立双路
    }
    dep[s]=0;
    // 对根节点进行一个搜索就行了
    for(int i=head[s];i!=-1;i=edge[i].next){
        init_fat(edge[i].to,s);
    }
    
    //cout<<find(3,5)<<endl;
    for(int j = 0;j<m;++j){
        int x,y;
        cin>>x>>y;
        cout<<find(x,y)<<endl;
    }
    
}
#include<iostream>
#include<cstring>
using namespace std;
#define maxn 410  // v加上u的点数
#define maxe 30010 // 最大的边数
// 前向星
int head[maxn],nex[maxe],to[maxe],cnt;
bool vis[maxn];   // 在这次搜索过程中，右边点是否已经被访问,每次匹配一个点都要清空一次
int pre[maxn];    // 右侧的点已经匹配的左侧的点
int un,vn,t;        // 左又侧数量，记得建立边的时候右边的序号加上左边点的数量
void add_edge(int u,int v){
    to[cnt]=v;
    nex[cnt]=head[u];
    head[u]=cnt++;
}

// 判断这个点是否能匹配
bool dfs(int u){
    for(int i=head[u];~i;i=nex[i]){
        if(!vis[to[i]]){
            vis[to[i]]=true;  // 记录右边这个结点被访问了
            // 如果右边这个点还没匹配左边的点
            // 或者它已经匹配了但是现在匹配的点能找到新的点(不会是to[i],因为这个标记了)
            if(pre[to[i]]==0||dfs(pre[to[i]])){
                pre[to[i]]=u;
                return true;    // 匹配成功
            }
        }
    }
    // 找完所有的点都找不到了，就匹配失败
    return false;

}
void init(){
    for(int i=0;i<maxn;++i){
        head[i]=-1;
        pre[i]=0;
    }
    cnt=0;
}



int main(){
    //freopen("test/A.in","r",stdin);
    
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&un,&vn);
        init();
        for(int i =1;i<=un;++i){
            int k;
            scanf("%d",&k);
            while(k--){
                int j;
                scanf("%d",&j);
                j+=un;
                add_edge(i,j);
            }
        }
        bool flag=true;
        for(int i=1;i<=un;++i){
            memset(vis,false,sizeof(vis));
            if(!dfs(i)){
                flag=false;
                break;
            }
        }
         
        if(flag){
            printf("YES\n");
        }else{
           printf("NO\n");
        }
    }
}
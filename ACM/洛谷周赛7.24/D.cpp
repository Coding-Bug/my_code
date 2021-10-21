#include<iostream>
using namespace std;
#define  long long int
#define maxn 50004
int head[maxn+1];  // 表头
int cnt=0;       // 边数
int val[maxn+1];   // 当前结点最大时间值
int din[maxn+1];   // 当前结点的入度
typedef struct Edge{
    int to;
    int next=-1;
    int weight;
}Edge;
Edge edge[maxn+1];

void add_edge(int from,int to,int w){
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    edge[cnt].weight=w;
    head[from]=cnt++;

}

int n,m;
int main(){
    //freopen("test/P1807_5.in","r",stdin);
    //freopen("test/H.out","r",stdin);
    cin>>n>>m;
    for(int i = 1;i<=maxn;++i){
        din[i]=0;
        val[i]=0;
        head[i]=-1;
    }
    for(int i = 0;i<m;++i){
        int x,y,w;
        cin>>x>>y>>w;
        din[y]++;
        add_edge(x,y,w);
    }  
    // 把除了1意外的入度为0的点干掉
   bool flag=true;
    while(flag){
        flag=false;
        for(int i = 2;i<=n;++i){
            if(din[i]!=0){
                continue;
            }
            flag=true;
            din[i]=-1;
            for(int j = head[i];j!=-1;j=edge[j].next){
                // 更新终点的入度和权值
                din[edge[j].to]--;
            }

        }
    }
     flag=true;
    while(flag){
        flag=false;
        for(int i = 1;i<=n;++i){
            if(din[i]!=0){
                continue;
            }
            flag=true;
            din[i]=-1;
            for(int j = head[i];j!=-1;j=edge[j].next){
                // 更新终点的入度和权值
                din[edge[j].to]--;
                val[edge[j].to]=max(val[i]+edge[j].weight,val[edge[j].to]);
            }

        }
    }
    if(val[n]==0){
      cout<<"-1"<<endl;;
    }else{
        cout<<val[n]<<endl;
    }
}
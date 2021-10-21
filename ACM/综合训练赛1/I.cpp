#include<iostream>
#include<queue>
using namespace std;
#define maxn 2000
#define maxm 300000
typedef struct{
    int to;
    int next;
}Edge;
Edge edge[maxm];
int head[maxn];
int cnt=0;
int n=0;
int in[maxn];
int a[maxn];
void add_edge(int u,int v){
     edge[cnt].to=v;
     edge[cnt].next=head[u];
     head[u]=cnt++;
}

void init(){
    for(int i = 0;i<maxn;++i){
        head[i]=-1;
        in[i]=0;
    }
}

void top(){
    queue<int>  Q;
    for(int i =1;i<=n;++i){
        if(in[a[i]]==0){
            Q.push(a[i]);
        }
    }
    while(!Q.empty()){
        int p=Q.front();
        Q.pop();
        for(int i = head[p];i!=-1;i=edge[i].next){
            int to=edge[i].to;
            in[to]--;
            if(in[to]==0){
                Q.push(to);
            }
        }
    }
}
int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>n;
   
    for(int i = 1;i<=n;++i){
        int x,m,c;
        cin>>x>>m;
        a[i]=x;
        for(int j = 1;j<=m;++j){
            cin>>c;
            add_edge(x,c);
            in[c]++;
        }
    }
    top();   // 拓扑排序
    int ans=0;
    for(int i = 1;i<=n;++i){
        if(in[a[i]]>0){
           ans++;
        }
    }

    if(ans==0){
        cout<<"YES"<<endl;
    }else{
        cout<<ans<<endl;
    }
    
}
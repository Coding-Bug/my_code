#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define maxe 250100
#define maxn 510
int t,s,n;
// edge存的是边的序号
int u[maxe],v[maxe],edge[maxe],fa[maxn];
double w[maxe];
int cnt=0;  // 边数
int xpos[maxn];
int ypos[maxn];  
bool cmp(int a,int b){return w[a]<w[b]?true:false;}
int find(int x){return x==fa[x]?x:x=find(fa[x]);}
double cal(int a,int b){return sqrt((xpos[a]-xpos[b])*(xpos[a]-xpos[b])+(ypos[a]-ypos[b])*(ypos[a]-ypos[b]));}
// num是需要的边数
double kruskal(int num){
    int count=0;
    // 对边进行排序
    sort(edge,edge+cnt,cmp);
    for(int i = 0;i<cnt;++i){
        int p=edge[i];
        int x=find(u[p]);
        int y=find(v[p]);
        if(x!=y){
            fa[x]=y;
            count++;
            if(count==num){
                return w[p];
            }
        }
    }
    return 0;
}
void init(){
    for(int i =0;i<maxn;++i){
        fa[i]=i;
    }
    for(int i=0;i<maxe;++i){
        w[i]=0;
        edge[i]=i;
    }
    cnt=0;
}


int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    
    while(t--)
    {
        init();
        cin>>s>>n;
        for(int i=1;i<=n;++i){
            cin>>xpos[i]>>ypos[i];
        }
        for(int i = 1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                u[cnt]=i;
                v[cnt]=j;
                w[cnt++]=cal(i,j);
            }
        }
        printf("%.2f\n",kruskal(n-s));
    }
    
}

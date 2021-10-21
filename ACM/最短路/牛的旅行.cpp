#include<iostream>
#include<cmath>
using namespace std;
#define maxn 154
#define INF 100000000000000000

// 牧区
typedef struct Node{
    int x;
    int y;
}Node;

Node node[maxn];
int N;
double adj[maxn][maxn];
double dis[maxn];
char str[maxn][maxn];
double ans=INF;    // 更新之后两个牧场的最大值的最小值
// 计算两点的距离
double cal (Node a,Node b){
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

// 建立矩阵
void fun1(){
    for(int i = 0;i<N;++i){
        for(int j = 0;j<N;++j){
            for(int k = 0;k<N;++k){
                if(adj[j][k]>adj[j][i]+adj[i][k]){
                    adj[j][k]=adj[j][i]+adj[i][k];
                }
            }
        }
    }
}


int main(){
    //freopen("test/A.in","r",stdin);
    cin>>N;
    for(int i = 0;i<N;++i){
        cin>>node[i].x>>node[i].y;
        dis[i]=0;
    }
    for(int i = 0;i<N;++i){
        cin>>str[i];
    }
    
    
    for(int i = 0;i<N;++i){
        for(int j = 0;j<N;++j){
            char c=str[i][j];
            if(i!=j&&c=='0'){
                adj[i][j]=INF;
                continue;
            }
            if(c=='0'){
                adj[i][j]=0; 
            }else{
                adj[i][j]=cal(node[i],node[j]); 
            }
        }

    }

    fun1();   // 标准算一遍矩阵
    // for(int i = 0;i<N;++i){
    //     for(int j = 0;j<N;++j){
    //         cout<<adj[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    double ans2=0;
    for(int i = 0;i<N;++i){
        for(int j = 0;j<N;++j){
           if(adj[i][j]!=INF){
               if(adj[i][j]>dis[i]){
                   dis[i]=adj[i][j];
                   
               }
               if(dis[i]>ans2){     // 求当前牧场的最大直径
                    ans2=dis[i];
                }
           }
        }
    }
    
    double ans1=INF;
    // 求出两个牧场经过i，j连接的直径并用这个直径更新连接牧场的最小直径
    for(int i=0;i<N;++i){
        for(int j = 0;j<N;++j){
            if(adj[i][j]==INF){
               double temp=cal(node[i],node[j]);
               double d=dis[i]+dis[j]+temp;  // 由i，j两个点连接后得到的两个牧场的直径
               // 看看这个直径是不是连接这两个农场的最小直径
               ans1=min(ans1,d);
            }
        }
    }
    ans = max(ans1,ans2);
    printf("%.6f\n",ans);
}
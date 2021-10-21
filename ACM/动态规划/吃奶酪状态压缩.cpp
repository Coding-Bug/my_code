#include<iostream>
#include<math.h>
using namespace std;
#define maxn 17
#define INF 1000000000

// 状态1为可以走，状态0为已经不能走了

typedef struct Node{
    double x;
    double y;
}Node;
Node node[maxn];
int cnt=1;
double cal(int i,int j){
    return sqrt((node[i].x-node[j].x)*(node[i].x-node[j].x)+(node[i].y-node[j].y)*(node[i].y-node[j].y));
}
double dp[maxn][1<<16];  // 二维开到16位  // dp[i][j]表示现在在i点，并且状态为j时要走的最短距离
int main(){
    //freopen("test/A.in","r",stdin);
    int n;
    cin>>n;
    node[1].x=node[1].y=0;   // 原点
    for(int i = 2;i<=n+1;++i){
        cin>>node[cnt].x>>node[cnt].y;
        cnt++;
    }
    n=n+1;
    const int T=(1<<n);  //最大状态+1，这样T-1的位数就是所有全部都没有选的状态

    //初始化边界
    for(int i = 1;i<=n;++i){
        for(int j = 0;j<T;++j){
            dp[i][j]=INF;
        }
    }

    // 还有就是都只剩一个的时候
    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=n;++j){
            dp[i][1<<(j-1)]=cal(i,j);    // 都只剩下一个的时候那么就是i到剩下没走那个的距离
        }
    }
    for(int i =1;i<=n;++i){
        dp[i][0]=0;             // 全部走完了，那么就是0，就没走
    }

    // 动态规划
    for(int j = 1;j<T;++j){
        for(int i = 1;i<=n;++i){
            if(j&(1<<(i-1))==1){   // 如果这个点还没走，那么不适合这种状态
               continue;
            }
            for(int k = 1;k<=n;++k){   // 枚举
                if((j&(1<<(k-1)))==0){    // 我们要枚举的是还没有走过的点
                    continue;
                }
                // 当前在i点，状态为j，要走剩下的路所需要的时间，因为我们是从要走的少推到要走的多的
                // 这里默认把起点设置为n，因为只有到n，才把所有点考虑完了
                // 前面的点，是不包含后面的点的，因为后面还没算出来
                // 所有只有最后一个点，才能作为起点
                dp[i][j]=min(dp[i][j],dp[k][j-(1<<(k-1))]+cal(i,k));
            }
        }
    }
    for(int i = 1;i<=n;++i){
        for(int j =1;j<T;++j){
            cout<< dp[i][j]<<" ";
        }
        cout<<endl;
    }


    // 因为没有虚拟终点，所以dp[n][T-1]就是终点
    // 上面起点默认为n
    printf("%.2f",dp[n][T-1]);
}
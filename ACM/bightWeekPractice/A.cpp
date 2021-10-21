#include<bits\stdc++.h>
using namespace std;

int T;      // 测试用例
int N;      // 骨头数
int V;      // 背包容量
int VOL[1002];   // 每个骨头所对应的体积
int VAL[1002];   // 骨头对应的价值
int best[1002]={0};

int main(){
    //freopen("test/A.txt","r",stdin);
    scanf("%d",&T);  
    while(T>0){
        scanf("%d%d",&N,&V);
        memset(best,0,sizeof(best));
        for(int i = 1;i<=N;++i){
            scanf("%d",&VAL[i]);
        }
        for(int i = 1;i<=N;++i){
            scanf("%d",&VOL[i]);
        }
        // 动态规划
        for(int i = 1;i<=N;++i){
            for(int j=V;j>=0;--j){
                if(VOL[i]>j){    // 剩余i个物品，剩余体积比第i个小的情况能取第i个
                   break;
                }else{
                    best[j]=max(best[j],best[j-VOL[i]]+VAL[i]);
                }
            }
        }

        printf("%d\n",best[V]);
        T--;
    }
}
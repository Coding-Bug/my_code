#include<bits\stdc++.h>
using namespace std;
int val[1002];     // 各结点的权值
int ans;
int MAX[1002];    // 到某个位置的时候的最大上升子序列
int main(){
    int N;
    freopen("test/B.txt","r",stdin);
    scanf("%d",&N);
    while(N!=0){
        ans = 0;
        for(int i=1;i<=N;++i){
            scanf("%d",&val[i]);
        }
        memset(MAX,0,sizeof(MAX));

        for(int i = 1;i<=N;++i){
            MAX[i]=val[i];       // 刚开始最大子序列是本身

            /*往前搜看看能否把*/
            for(int j = 1;j<i;++j){
                if(val[j]<val[i]){
                    MAX[i]=max(MAX[j]+val[i],MAX[i]);    // 试着更新第i个位置的最大上升子序列
                }
            }
            if(MAX[i]>ans){
                ans = MAX[i];
            }
        }

        printf("%d\n",ans);

        scanf("%d",&N);
    }
}
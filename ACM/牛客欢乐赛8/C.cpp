#include<iostream>
#include<algorithm>
// 01背包变形
using namespace std;
int fllowerA[303];
int fllowerB[303];
int dressA[303];
int dressB[303];

long long dp[140][7][7];
long long ans=0;
int n,m,d; // 玩家仓库的从者数、概念礼装数和cost值上限

int main(){
    //freopen("test/C.txt","r",stdin);
    cin>>n>>m>>d;
    for(int i = 0;i<n;++i){
        cin>>fllowerA[i]>>fllowerB[i];
    }
    for(int i = 0;i<m;++i){
        cin>>dressA[i]>>dressB[i];
    }

    

    //先是没有礼装的情况,最大允许cost为j,最大从者数为k，礼装数为0的情况
    //目的是求出最大从者数为1-5，礼装数为0得各种情况，从而下面进一步求出礼装最大数非零的情况
    for(int i = 0;i<n;++i){
        // 容量要从大到小，才能保证这次用到的是上一个i算的，因为省略了一维
        // 如果从小到大，会用可能会再选取过第i个的基础上再选一次第i个
        // 所以dp要省略维度就要保证当前条件下前面的结果对后面的结果没有影响
        for(int j = d;j>=fllowerB[i];--j){  
            for(int k = 1;k<=5;++k){
                // 比较在最大cost为j，最大从者数为k，礼装数为0的情况下，选这件和不选这件哪个大。
            dp[j][k][0]=max(dp[j][k][0],dp[j-fllowerB[i]][k-1][0]+fllowerA[i]);
            ans=max(ans,dp[j][k][0]);   // 在不选取礼装的情况下记录最大值
        }
        }
        
    }
   
    // 根据上面求出在最大从者的允许数为5，且最大礼装的允许数也为5的情况下，cost最大为d时的最大atk
    // 因为礼装要以从者为前提，所以上面先求得从者得情况
    for(int i =0;i<m;++i){
        for(int j=d;j>=dressB[i];--j){
            for(int k = 1;k<=5;++k){
                for(int l=1;l<=k;++l){  // 礼装数不饿能大于从者数
                    dp[j][k][l]=max(dp[j][k][l],dp[j-dressB[i]][k][l-1]+dressA[i]);
                    ans=max(ans,dp[j][k][l]); // 记录在选取礼装的情况下的最大值
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}

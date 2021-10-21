#include<iostream>
using namespace std;
int main(){
    //freopen("test//2.txt","r",stdin);
    int h[1002];
    int s[1002];
    int w[1002];
    long long int dp[302][302];
    int n;   // 有多少个怪
    int H;   // yuna的生命值
    int S;   // yuna的体力值
    cin>>n>>H>>S;
    
    for(int j = 0;j<302;++j){
        for(int k = 0;k<301;++k){
            dp[j][k]=0;
        }
    }
    for(int i=0;i<n;++i){
        cin>>h[i]>>s[i]>>w[i];
    }

    // 动态规划
    for(int i = 0;i<n;++i){
        for(int j = H;j>h[i];--j){    // j是当前情况主角剩余的生命值,j要先从最大值考虑
            for(int k = S;k>=0;--k){   // k是当前情况主角剩余的耐力值
                if(j+k>h[i]+s[i]){   // 第i个这种情况下可以取
                   if(k>=s[i]){  // 不用扣生命值的情况，判断打不打这个怪
                      dp[j][k]=max(dp[j-h[i]][k-s[i]]+w[i],dp[j][k]);    // 这里因为是向前的，所以先算前面的会影响后面的，达不到滚动效果
                   }else{      // 扣生命值的情况，判断打不打这个怪
                      dp[j][k]=max(dp[j-h[i]-(s[i]-k)][0]+w[i],dp[j][k]);
                   } 

                }
            }
        }
    }


    cout<< dp[H][S]<<endl;
    return 0;
}
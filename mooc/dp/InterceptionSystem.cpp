#include<bits/stdc++.h>
using namespace std;
int main(){
    //freopen("test/A.txt","r",stdin);
    int k;    // 敌国导弹数
    int a[26];// 敌国导弹的高度
    //bool isEnd[26];   // 标记导弹是否最长不递增子序列的结尾
    int dp[26];   // dp数组
    int ans=0;    // 答案
    int Max=0;    // 每个结点比他小的子序列的最长值
    //int path=0;   // 暂时存放每个结点的前驱
    cin>>k;
    for(int i = 0;i<k;++i){
        cin>>a[i];
        dp[i]=0;
    }  

    // 初始化为每个导弹都是最长不递增子序列的尾
   // memset(isEnd,true,sizeof(isEnd));
    

    // 求子序列
    for(int i = 0;i<k;++i){
        Max = 0;
       // path=-1;
       for(int j = 0;j<i;++j){
           if(a[j]>=a[i]&&a[j]>Max){
               Max = dp[j];
               //path = j;
           }
       }

       // 更新a[i]以及标记第path个不是末尾
       dp[i]=Max+1;
       //isEnd[path]=false;
    }

    // 统计最大不递减子序列个数
    for(int i = 0;i<k;++i){
        if(dp[i]>ans){
            ans = dp[i];
        }
    }
    cout<<ans<<endl;
    return 0;
}
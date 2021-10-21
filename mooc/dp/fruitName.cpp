#include<bits/stdc++.h>
using namespace std;
// 试用最长递增子序列求

int main(){
    //freopen("test/B.txt","r",stdin);
    char arr1[88];
    char arr2[88];
    
    char arr3[88];   // 存放新名字
    int Larr3=0;
    int dp[88][88];
   
    
     cin>>arr1;
     cin>>arr2;
    int Larr1=strlen(arr1);  
    int Larr2=strlen(arr2);
    // 因为要用到左上角，所以第0行和第0列要初始化为0，dp从11开始
    // 初始化dp数组
    for(int i = 0 ;i<=Larr1;++i){
        dp[0][i]=0;
    }

    for(int i = 0;i<=Larr2;++i){
        dp[i][0]=0;
    }


    // 求dp数组
    for(int i = 1;i<=Larr2;++i){
        for (int j = 1;j<=Larr1;++j){
           if(arr1[j-1]==arr2[i-1]){
              dp[i][j]=dp[i-1][j-1]+1;
           }else{
               dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
           }
        }
    }


    // 取得新名字的逆序
    int i = Larr2;
    int j = Larr1;
    while(i>0&&j>0){
        if(dp[i][j]==dp[i-1][j]){  // 等于上面的
           arr3[Larr3++]=arr2[i-1];
           --i;
        }else if(dp[i][j]==dp[i][j-1]){// 等于左边的
           arr3[Larr3++]=arr1[j-1];
           --j;
        }else{   // 等于左上角加1
            arr3[Larr3++]=arr1[j-1];
            i--;
            j--;
        }

    }

    // 如果Larr2有剩余
    while(i>0){
        arr3[Larr3++]=arr2[i-1];
        --i;
    }
    // 如果Larr3有剩余
     while(j>0){
        arr3[Larr3++]=arr1[j-1];
        --j;
    }

    // 输出
    for(int k =Larr3-1;k>=0;--k){
        cout<<arr3[k];
    }
    cout<<endl;
}
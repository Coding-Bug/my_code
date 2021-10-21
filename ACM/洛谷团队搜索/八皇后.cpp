#include<iostream>
using namespace std;
int ans;   // 解的个数
int x[15];  // 解向量
int num=0;  // 解向量的元素数量
bool y[15]; // 纵坐标是否还能放
int n;
bool a[15][15];  // 棋盘
int step[15][15];  // 在第几步被干掉

// 判断该点能不能落子
bool judge(int y,int x){

     // 判断左上角
     int j=x-1;
     int i=y-1;
     while(i>=0&&j>=0){
         if(a[i][j]==true){
           return false;
         }
         i--;
         j--;
     }
     j=x+1;
     i=y-1;

     //右上角
      while(i>=0&&j<n){
         if(a[i][j]==true){
           return false;
         }
         i--;
         j++;
     }

     
     return true;

}
void dfs(int i){
    // 递归出口
    if(i==n){ 
       ans++;
       if(ans<=3){
           int j;
           for(j = 0;j<num-1;++j){
              cout<<x[j]+1<<" ";
           }
           cout<<x[j]+1<<endl;
       }
       return;
    }
    for(int j = 0;j<n;++j){
    
        if(y[j]&&judge(i,j)){// 如果这个点能放
            a[i][j]=true; // 标记为该点下过了
            y[j]=false;
            x[num++]=j;
            dfs(i+1);
            y[j]=true;
            a[i][j]=false;
            num--;
        }
    }
}
int main(){
    for(int i = 0;i<15;++i){
        y[i]=true;
        for(int j = 0;j<15;++j){
            a[i][j]=false;
        }
    }
    cin>>n;
    dfs(0);   // 从1到n
    cout<<ans<<endl;
    
}
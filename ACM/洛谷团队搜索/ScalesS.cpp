#include<iostream>
#include<queue>
using namespace std;
long long N,C;
long long W[1004]={0};
long long x[1004]={0};
int num;
long long sum[1004]={0};
long long ans=0;

// 从后往前搜索，因为是前面影响后面，从后往前就会方便
void dfs(int i,long long now){
    if(now+sum[i]<ans){   // 极限都不够，剪掉
        return;
     }
     if(now>ans){// 要时刻更新答案，不然到就会发生一些错误
        ans=now;
     }  
     if(i==0){
         return;
     }
     
     if(now+W[i]>C){   // 不能选第i个
         dfs(i-1,now);  
         return;
     }

     // 先判断取得，尽量得到最大，以后剪得越多
     if(num>=2){
         if(W[i]+x[num-1]<=x[num-2]){   // 符合要求才要
            x[num++]=W[i];
            dfs(i-1,now+W[i]);
            num--;
         }
         
     }else{
            x[num++]=W[i];
            dfs(i-1,now+W[i]);
            num--;
     }

     dfs(i-1,now);

    
}
int main(){
    //freopen("test/A.txt","r",stdin);
    cin>>N>>C;
    for(int i = 1;i<=N;++i){
        cin>>W[i];
        if(W[i]>C){
            N=i-1;
            break;
        }
        sum[i]=sum[i-1]+W[i];
    }
    dfs(N,0);
    cout<<ans<<endl;


}
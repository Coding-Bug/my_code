#include<bits/stdc++.h>
using namespace std;
typedef struct Time{
    int A;
    int B;
    bool isUsed=false;
}Time;

bool cmp(Time a,Time b){
    return a.B<b.B;
}
int main(){
    //freopen("test/Cow.txt","r",stdin);
      Time time[50002];
      int n;
      int ans = 0;
      int CowN=0;   // 已经挤了的奶牛数
      int NowT=0;   // 上一个结束之时间 
      cin>>n;
      for(int i =0;i<n;++i){
          cin>>time[i].A>>time[i].B;
      }
      sort(time,time+n,cmp);
      while(CowN!=n){
          NowT = 0;
          for(int i =  0;i<n;++i){
           if(!time[i].isUsed&&time[i].A>NowT){
               time[i].isUsed=true;
               NowT=time[i].B;
               CowN++;
           }
          }
          ans++;
      }

      cout<<ans<<endl;


}
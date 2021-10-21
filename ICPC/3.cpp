#include<iostream>
#include<queue>
using namespace std;
int main(){
    //freopen("test//3.txt","r",stdin);
    int a[5];
    long long int ans=0;      // 要消耗的金币数
    cin>>a[1]>>a[2]>>a[3];    // 输入三种石头的数量
    
    // 一个石头的和两个石头的组3的倍数是最划算的，优先，最后剩下的各自对自己组3的倍数
    if(a[1]>=a[2]){    // 当石头数为1的堆多时
      ans+=a[2]*2;
      a[1]=a[1]-a[2];
      // 算剩下的a[1],剩下是3个a[1]组一次，
      ans+=(a[1]/3)*3;
      // 若最后a[1]还有两块，则还要加
      if(a[1]%3==2){
          ans+=1;
      }
    }else{            // 石头数为2的多
      ans+=a[1]*2;
      a[2]=a[2]-a[1];
      // 剩下的a[2]三块组一次 ，每次花6
      ans+=(a[2]/3)*6;
      // 若最后a[2]还有两块，则还要加
      if(a[2]%3==2){
          ans+=4;
      }
    }
    
    cout<<ans<<endl;
    
}
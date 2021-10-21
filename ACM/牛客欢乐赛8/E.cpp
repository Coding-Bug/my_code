#include<iostream>
using namespace std;
const long long mod =20100403;
int n , m;

// 求阶乘
long long fac(long long a){
    long long ans=1;
    for(long long i = a;i>=1;--i){
       ans=(ans*i%mod)%mod;
       ans=ans%mod;
    }
    return ans;
}
// 矩阵快速幂求逆元
long long Fpow(long long b,long long p){
    long long ans=1;
    while(p>0){
        if(p%2==0){
           b=(b*b)%mod;
           p=p/2;
        }else{
           ans=(ans*b)%mod;
           b=(b*b)%mod;
           p=p/2;
        }
    }
    return ans;
}
// 求组合数
long long C(int a,int b){
    long long a1=fac(a);  // 求分子
    long long b1=(fac(b)*fac(a-b))%mod; //分母
    //求b的逆元
    b1=Fpow(b1,mod-2);
    return ((a1%mod)*(b1%mod))%mod;

}
int main(){
    freopen("test/E.txt","r",stdin);
    cin>>n>>m;
    long long ans;
    ans=(C(n+m,n)-C(n+m,n+1)+mod)%mod; // 可能会求得附属，所以先加上模再取模，因为计算结果是分别取模之后的，所以小的可能本来就比mod小
    cout<<ans<<endl;
}
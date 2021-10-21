#include<iostream>
using namespace std;
int n;
int main(){
    cin>>n;
    int ans=0;
    // 从1到n，约数对应数的数量是不递增序列
    for(int i =1,j;i<=n;i=j+1){
        j=n/(n/i);    // j是对应数的数量为n/i的最大值
        ans+=(n/i)*(j-i+1);   // 将对应的数的个数为n/i的约数一次性贡献。
    }
    cout<<ans<<endl;
}
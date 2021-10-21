#include<iostream>
#include<algorithm>
using namespace std;
long long  a[1000004];
long long  S[1000004]; // 前缀和
int n;
long long ans=0;
int main(){
    //freopen("test/D.txt","r",stdin);
    cin>>n;
    long long sum=0;   // 求出一共的糖果数
    for(int i =0;i<n;++i){
        cin>>a[i];
        sum+=a[i];
    }
    long long avg = sum/n;  // 均值
    // 求减去均值之后的前缀和
    S[0]=a[0]-avg;
    for(int i = 1;i<n;++i){
        S[i]=S[i-1]+a[i]-avg;
    }
    sort(S,S+n); // 排序
    int mid = (n)/2; //中位数
    for(int i = 0;i<n;++i){
       ans+=abs(S[i]-S[mid]);
    }
    cout<<ans<<endl;
    
}
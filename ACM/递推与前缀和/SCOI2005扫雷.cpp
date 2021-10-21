#include<iostream>
using namespace std;
#define maxn 10004
int n;
int a[maxn]={0};   // 第二列
int b[maxn];   // 第一列

// 计算第一个点某种放置情况是否符合
bool cal(){
    for(int i = 2;i<=n+1;++i){
        b[i]=a[i-1]-b[i-1]-b[i-2];
        if(i==n+1&&b[i]!=0){
            return false;
        }
        if(b[i]<0){
           return false;
        }
    }
    return true;
}
int main(){ 
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i = 1;i<=n;++i){
        cin>>a[i];
    }
    int ans=0;
    if(cal()){
        ans++;
    }
    b[1]=1;
    if(cal()){
        ans++;
    }
    cout<<ans<<endl;



}
#include<iostream>
#include<math.h>
using namespace std;
#define ll  long long 
#define TLE ios::sync_with_stdio(0),cin.tie(0);
ll n,m,x1,x2;
int t;

// 求曼哈顿距离
ll cal(ll x1,ll y1,ll x2,ll y2){
    return (abs(x1-x2)+abs(y1-y2));
}

int main(){
    TLE;
    //freopen("test/A.in","r",stdin);
    cin>>t;
    //cin>>t;
    while(t--){
        cin>>n>>m>>x1>>x2;
        ll ans1,ans2,ans3,ans4;
        ll ans=0;
        ans1=cal(1,1,1,x1);// 上方繁殖到左边
        ans2=cal(n,x2,n,m); // 下面繁殖到右边
        ans3=n-1;     // 上下阻拦
        // 上下一起阻拦
        if(x1==x2){    // 两个在同一列
            ans4=(n-1)/2;
        }else{         // 不在同一列相当于直接把两个基地连起来
            ans4=(cal(1,x1,n,x2)-1)/2;
        }
        ans=ans1>ans2?ans2:ans1;
        ans=ans>ans3?ans3:ans;
        ans=ans>ans4?ans4:ans;
        cout<<ans*ans<<endl;
    }
}
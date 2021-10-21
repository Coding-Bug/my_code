#include<iostream>
using namespace std;
#define ll long long
#define maxn 1000006
typedef struct 
{
    ll d;
    ll s;
    ll t;
}Node;
Node q[maxn];
ll r[maxn];
ll de[maxn];   // 差分
ll sum[maxn];
ll temp[maxn];  // 存原数组
int n,m;

// 在第x个教室做一次判断
bool cal(int x){
     // 更新差分
     for(int i = 1;i<=x;++i){
         int l=q[i].s;
         int r=q[i].t;
         ll d=q[i].d;
         de[l]-=d;
         de[r+1]+=d;
     }
     
     
     // 利用差分求前缀和
     for(int i = 1;i<=n;++i){
         temp[i]=de[i]+temp[i-1];
         //sum[i]=sum[i-1]+temp[i];
     }

     // 恢复差分
     for(int i = 1;i<=x;++i){
         int l=q[i].s;
         int r=q[i].t;
         ll d=q[i].d;
         de[l]+=d;
         de[r+1]-=d;
     }

     // 判断第x个能否满足
     int l=q[x].s;
     int r=q[x].t;
     ll  d=q[x].d;
     for(int i = 1;i<=n;++i){
         if(temp[i]<0){
             return false;
         }
     }
     return true;
}
int main(){
    //freopen("test/B.in","r",stdin);
    cin>>n>>m;
    for(int i =1;i<=n;++i){
        cin>>r[i];
        de[i]=r[i]-r[i-1];
    }
    for(int j =1;j<=m;++j){
        cin>>q[j].d>>q[j].s>>q[j].t;
    }
    
    ll l=1;
    ll r=m;
    ll mid;
    while(l<r){
        //cout<<l<<" "<<r<<endl;
        mid=(l+r)/2;
        bool flag=cal(mid);
    
        // 如果到x还能满足，那么就往后,因为要求不满足的，所以mid不要了
        if(flag){
            l=mid+1;   
            if(l==r){
                mid=l; // 这里记得更新不然出去的mid不是我们想要的mid

            }
        }else{
            r=mid;
        }   
    }

    // 这里应该是再判断一下mid满不满足
    // 如果还满足，就输出0
    if(mid>=m){
        cout<<"0"<<endl;
        return 0;
    }

    cout<<"-1"<<endl;
    cout<<mid<<endl;
}
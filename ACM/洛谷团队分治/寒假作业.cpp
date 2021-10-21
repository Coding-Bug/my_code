#include<iostream>
#include<algorithm>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0)
int n,k;
int a[100004];
int b[100004];   // 左边那段
int bn=0;
int c[100004];
int cn=0;
bool cmp(int a,int b){
    return a>=b;
}
long long  divide(int l,int r){
    if(l>r){
        return 0;
    }
    if(l==r){
        if(a[l]>=0){
           return 1;
        }else{
            return 0;
        }
    }

    int mid=(l+r)/2;
    long long S=0;
    S+=divide(l,mid);
    S+=divide(mid+1,r);
    bn=0;
    cn=0;
    b[bn++]=a[mid];
    c[cn++]=a[mid+1];
    // 存后缀和前缀
    for(int i = mid-1;i>=l;--i){
       b[bn]=b[bn-1]+a[i];
       bn++;
    }
    for(int j = mid+2;j<=r;++j){
        c[cn]=c[cn-1]+a[j];
        cn++;
    }
    // 后缀和前缀不怕排序的
    sort(b,b+bn,cmp);
    sort(c,c+cn,cmp);
    
    // 这里不用两个for，不然会爆掉
    // 左边用最小的遍历，右边从最大的开始遍历，这样右边就可以继承，优化了时间
    // 以左边为基准，每次去匹配右边尽可能多的
    // 因为左边是从小到达，所以当前能匹配成功的，那么b[i+1]肯定也能
    for(int i =bn-1,j=0;i>=0;--i){
          while(j<cn&&b[i]+c[j]>=0) ++j;
          S+=j;
    }

    return S;

}
long long ans;

int main(){
    TLE;
    //freopen("test/A.txt","r",stdin);
    cin>>n>>k;
    for(int i = 0;i<n;++i){
        cin>>a[i];
    }
    bool flag=false;
    for(int i = 0;i<n;++i){
        a[i]-=k;       // 由求平均数变成求和
        if(a[i]>0){
            flag=true;
        }
    }
    if(!flag){
        cout<<0<<endl;
    }
    ans=divide(0,n-1);
    cout<<ans<<endl;


}
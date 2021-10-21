#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 4003
int a[maxn];
int b[maxn];
int cnt[maxn];   //记着这个数之前找到了多少个
bool flag=false; //是否找到过aa
bool cmp(int a,int b){
    return a<b;
}
int n;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i =0;i<n;++i){
        cin>>a[i];
        b[i]=a[i];
    }

    // 不用map，练习一下离散化
    sort(b,b+n,cmp);
    int l=unique(b,b+n)-b;

    for(int i =0;i<n;++i){
        a[i]=lower_bound(b,b+l,a[i])-b+1;
    }

    int p=0;   // 上一次找到的位置
    int ans=0;
    for(int i = 0;i<n;++i){
        cnt[a[i]]++;
        if((cnt[a[i]]==2&&flag)||cnt[a[i]]==4){   // 之前已经找到了两个并且，现在又找到了两个
           ans++;
           for(int j = p;j<=i;++j){
               cnt[a[j]]=0;
           }
           flag=false;    // 重新标记为没找到
           p=i+1;
           continue;
        }
        if(cnt[a[i]]==2){
          flag=true;      // 标记找到了两个
        }
    }
    cout<<ans<<endl;
    


}
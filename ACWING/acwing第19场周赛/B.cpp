#include<iostream>
using namespace std;
#define maxn 1005
#define ll long long
int n,w;
ll a[maxn];
ll Max;
ll Min;
ll Sum=0;
int main(){
    cin>>n>>w;
    for(int i = 0;i<n;++i){
      cin>>a[i];
    }
    Min=Max=a[0];
    for(int i = 0;i<n;++i){
      Sum+=a[i];
      if(Sum<-1*w){
        cout<<0<<endl;
        return 0;
      }

      if(Sum>w){
        cout<<0<<endl;
        return 0;
      }
      Min=min(Sum,Min);
      Max=max(Sum,Max);
    }

    if(Min>0){
      Min=0;
    }else{
      Min=abs(Min);
    }

    if(Max<0){
      Max=0;
    }

    ll ans=w-Max-Min+1;
    if(ans<0){
      ans=0;
    }
    cout<<ans<<endl;


   


}
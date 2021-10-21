#include<iostream>
#include<unordered_map>
using  namespace std;
#define maxn 200007
int N;
long long a[maxn];
long long C;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>N>>C;
    unordered_map<long long,int> mp;
    for(int i = 0;i<N;++i){
       cin>>a[i];
       long long temp=a[i]+C;
       if(mp.count(temp)==0){
           mp[temp]=1;
       }else{
           mp[temp]++;
       }
    }
    long long ans=0;
    for(int i = 0;i<N;++i){
        if(mp.count(a[i])==0){
            continue;
        }else{
            ans+=mp[a[i]];
        }  
    }
    if(C==0){
        ans-=N;
    }
    cout<<ans<<endl;


}
#include<iostream>
#include<math.h>
using namespace std;
unsigned long long n,S,L;
unsigned long long A[200005];
unsigned long long ans=0;
unsigned long long u[200005];
unsigned long long l=0;
unsigned long long r=1e18;

int main(){
    
    //freopen("test/A.txt","r",stdin);
    cin>>n>>S>>L;
    for(int i=0;i<n;++i){
        cin>>A[i];
    }
    for(int j = 0;j<n;++j){
        cin>>u[j];
    }
    while(r!=l){
        ans=(r+l)/2;
        unsigned long long sum=0;
        for(int i =0;i<n;++i){
           if(A[i]+u[i]*ans>=L){
               sum+=A[i]+u[i]*ans;
           }
        }
        if(sum>S){
            r=ans;
        }else if(sum<S){
            if(r-l==1){
                ans=r;
                break;
            }
            l=ans;
        }else{
            break;
        }
    }

    cout<<ans<<endl;
}
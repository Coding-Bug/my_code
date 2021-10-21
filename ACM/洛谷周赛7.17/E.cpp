#include<iostream>
using namespace std;
long long  a[200004];
long long ans=0;
int main(){
    //freopen("test/E.txt","r",stdin);
    int N;
    cin>>N;
    for(int i = 0;i<N;++i){
        cin>>a[i];
    }
    int i=0;
    int j=N-1;
    while(i<j){
        int kl=0;
        int kr=0;
        int k;
        bool flagl=true;
        bool flagr=true;
        while(a[j]<a[j-1]){
            --j;
            if(i==j){
                cout<<ans<<endl;
                return 0;
            }  
            
        }
         while(a[i]<a[i+1]){
            ++i;
            if(i==j){
                cout<<ans<<endl;
                return 0;
            }  
        }
        kr=a[j]-a[j-1]+1;
        kl=a[i]-a[i+1]+1;
        if(kr==kl){
            k=kl;
            flagl=flagr=true;
        } else if(kr>kl){
            k=kl;
            a[j]-=kl;
            flagr=false;
            flagl=true;
        }else{
            k=kr;
            a[i]-=kr;
            flagl=false;
            flagr=true;
        }
        
        if(i==j-1){
            if(a[i]==a[j]){
            cout<<ans+1<<endl;
            }else{
                cout<<ans<<endl;
            }
            return 0;
        }
        ans+=k;
        if(flagl)
        ++i;
        if(flagr)
        --j;
        
               
    
    }
    cout<<ans<<endl;
    

}
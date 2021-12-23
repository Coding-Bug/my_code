#include<iostream>
using namespace std;
#define ll long long
int t;
ll a,b,c;

int main(){
   // freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>a>>b>>c;
   
            if(abs(a+c-2*b)%3==0){
                cout<<0<<endl;
            }else{
                cout<<1<<endl;
            }
        

    }
}
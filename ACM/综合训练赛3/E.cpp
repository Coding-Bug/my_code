#include<iostream>
using namespace std;
int T;
int n;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>T;
    while(T--){
        cin>>n;
        if(n%4!=0){
            cout<<"October wins!"<<endl;
        }else{
            cout<<"Roy wins!"<<endl;
        }
    }

}
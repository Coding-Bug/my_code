#include<iostream>
using namespace std;
int N;
int a[102];
int b[102];
int sum=0;
int ans=0;
int main(){
    cin>>N;
    for(int i = 0;i<N;++i){
        cin>>a[i];
        sum+=a[i];
    }
    int avg=sum/N;
    for(int i =0;i<N;++i){
        b[i]=a[i]-avg;
    }
    sum=b[0];
    if(b[0] != 0){
        ans++;
    }
    for(int i = 1;i<N-1;++i){
        sum=sum+b[i];
        if(sum!=0){
            ans++;
        }
    }
    cout<<ans<<endl;


}
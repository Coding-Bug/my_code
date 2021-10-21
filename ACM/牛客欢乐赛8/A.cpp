#include<iostream>
using namespace std;
long long F[4];
long long  gcd(long long  x,long long  y){
    if(x%y==0){
        return y;
    }
    return gcd(y,x%y);
}
int main(){
    long long A,B,N;
    cin>>A>>B>>N;
        cout<<gcd(A,B)<<endl;
    
    return 0;
}
#include<iostream>
#include<cmath>
using namespace std;
#define MAX 100
int a[MAX];
int cnt=1;
int main(){
    a[0]=1;
    for(int i = 1;i<MAX;++i){
        a[i]=0;
    }
    int n;
    cin>>n;
    n=n+1;
    int C=0; // 进位
    for(int i = 0;i<n;++i){
       for(int j = 0;j<cnt;j++){
          a[j]=2*a[j]+C;
          if(a[j]>=10){
              C=a[j]/10;
              a[j]=a[j]%10;
          }else{
              C=0;
          }
          if(C!=0&&j==cnt-1){
              cnt++;
          }
       }
    }
    //减去2
    C=-2;
    for(int i= 0;i<cnt;++i){
        if(C==-1&&i==cnt-1&&a[cnt-1]==1){
            cnt--;
            break;
        }
        if(a[i]==0){
            a[i]=8;
            C=-1;
        }else if(a[i]==1){
            a[i]=9;
            C=-1;
        }else{
            a[i]=a[i]+C;
            C=0;
        }

        if(C==0){
            break;
        }
    }
    for(int i = cnt-1;i>=0;--i){
        cout<<a[i];
    }
    cout<<endl;
}
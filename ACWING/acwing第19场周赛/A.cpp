#include<iostream>
using namespace std;
#define maxn 1003

int t;
int n;
char str[maxn];
int main(){
  cin>>t;
  while(t--){
    cin>>n;
    cin>>str;
    bool ans=true;
    int cnt=1;
    char last;
    for(int i = 1;i<n;++i){
      if(str[i]==str[i-1]){
        cnt++;
      }else{
        cnt=1;
      }

      if(cnt==2&&str[i]=='1'){
        ans=false;
       break;
      }

      if(cnt==3&&str[i]=='0'){
        ans=false;
        break;
      }
    }
    if(n==1&&str[0]=='0'){
      ans=false;
    }else{
      if(str[0]=='0'&&str[1]=='0'){
        ans=false;
      }
      if(str[n-1]=='0'&&str[n-2]=='0'){
        ans=false;
      }
    }

    if(ans){
      cout<<"Yes"<<endl;
    }else{
      cout<<"No"<<endl;
    }




  }

}
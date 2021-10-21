#include<iostream>
#include<cstring>
using namespace std;
#define maxn 100008
int n,t;
char str[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>t;
    getchar();
    cin.getline(str,n+1,'\n');
    while(t--){
        bool flag=false;
        char c;
        int sum=0;
        char str0=str[0];
        if(str[n-1]=='1'){
            sum++;
        }
        if(str[1]=='1'){
            sum++;
        }
        if(sum==1){
           c='1';
        }else{
            c='0';
        }
        if(c!=str[0]){
            flag=true;
        }
        //cout<<c<<endl;
        for(int i =1;i<n-1;++i){
            sum=0;
            if(str[i-1]=='1'){
              sum++;
            }
            if(str[i+1]=='1'){
                sum++;
            }
            str[i-1]=c;
            if(sum==1){
                c='1';
            }else{
                c='0';
            }
          if(c!=str[i]){
            flag=true;
          }
        }
        // 第n个
        sum=0;
        if(str[n-2]=='1'){
            sum++;
        }
        if(str0=='1'){
            sum++;
        }
        str[n-2]=c;
            if(sum==1){
                c='1';
            }else{
                c='0';
            }
            if(c!=str[n-1]){
                flag=true;
             }
        str[n-1]=c;
        if(!flag){
            break;
        } 
        //cout<<str<<endl;
    }

    cout<<str<<endl;

}
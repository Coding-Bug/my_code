#include<iostream>
using namespace std;
#define maxn 55
int a[maxn];
bool vis[4];
char c[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>c;
    int cnt=0;
    for(int i =1;c[i]!='\0';++i){
       a[cnt++]=c[i]-'0';
    }

    if(a[cnt-1]==4){
        for(int e=1;e<=3;++e){
            cout<<"T";
            for(int i =0;i<cnt-1;++i){
                cout<<a[i];
            }
            cout<<e<<endl;
        }
        return 0;
    }
    for(int k=cnt-1;k>=0;--k){
        if(!vis[a[k]]){
            cout<<"T";
            for(int i = 0;i<k;++i){
                cout<<a[i];
            }
            cout<<4<<endl;
            vis[a[k]]=true;
        }
    }

    








}
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100000

int w,n;
int p[maxn];
int cnt=0;   // 分块数
int ret[maxn];  // 第i个块剩余空间
bool cmp(int a,int b){
    return a>b;
}
bool vis[maxn];
int main(){
    for(int i = 0;i<maxn;++i){
        vis[i]=false;
    }
    //freopen("test/A.in","r",stdin);
    cin>>w>>n;
    for(int i =0;i<n;++i){
        cin>>p[i];
    
    }
    for(int i = 0;i<maxn;++i){
        ret[i]=w;
    }
    sort(p,p+n,cmp);
    if(n!=0){
        ret[cnt]-=p[0];
        cnt++;
    }
    for(int i = 1;i<n;++i){
        bool flag=false;
        for(int j =0;j<cnt;++j){
            if(p[i]<=ret[j]&&!vis[j]){
                vis[j]=true;
                ret[j]-=p[i];
                flag=true;
                break;
            }
        }
        if(!flag){
            ret[cnt++]-=p[i];
            //cout<<cnt<<" "<<p[i]<<endl;
        }
    }
    cout<<cnt<<endl;
}
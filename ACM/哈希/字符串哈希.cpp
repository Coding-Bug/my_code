#include<iostream>
#include<cstring>
#include<unordered_map>
using namespace std;
#define maxn 10004
char str[maxn][maxn];
int hs[2][maxn];
int n;
long long mod[2]={1000000003,1000000007};
long long base[2]={131,1313};
void make_hash(int index,int len){
    hs[0][0]=0;
    hs[1][0]=0;
    for(int i=1,c;i<=len;++i){
       c=str[index][i];
       hs[0][i]=(hs[0][i-1]*base[0]+c)%mod[0];
       hs[1][i]=(hs[1][i-1]*base[1]+c)%mod[1];
    }
}
int main(){
    //freopen("test/B.in","r",stdin);
    cin>>n;
    unordered_map<long long,char*> mp;
    for(int i =0;i<n;++i){
        cin>>str[i];
        int l=strlen(str[i]);
        make_hash(i,l);  // 制造哈希
        mp[hs[0][l]^hs[1][l]]=str[i];
    }
    long long ans=0;
    cout<<mp.size()<<endl;
}
#include<iostream>
#include<string>
using namespace std;
#define maxn 1000004
int trie[maxn][12];
int top=0;
int mrk[maxn];
int t,n;
string s;
void Init(){
    for(int i = 0;i<maxn;++i){
        for(int j = 0;j<12;++j){
            trie[i][j]=0;
        }
        mrk[i]=0;
    }

    top=0;
}
bool trie_init(string str){
     int l=str.length();
     int now=0;
     bool flag1=false;    // 是否有新增结点
     bool flag2=false;    
     for(int i = 0;i<l;++i){
         int c=str[i]-'0';
         //cout<<c<<" ";
         if(!trie[now][c]){
            trie[now][c]=++top;
            flag1=true;
         }
         now=trie[now][c];
         if(mrk[now]){
             return true;
         }
     }


     // 如果自己没有新增的，那么它是别人的前缀
     if(!flag1){
         return true;
     }
     mrk[now]=1;  // 这个结点是一个串
     return false;
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        // 初始化
        Init();
        cin>>n;
        bool flag=false;
        for(int i = 0;i<n;++i){
            cin>>s;
            if(!flag){
               flag=trie_init(s);
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
}
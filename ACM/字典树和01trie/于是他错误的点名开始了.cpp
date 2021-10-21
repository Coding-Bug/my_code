#include<iostream>
#include<cstring>
using namespace std;
#define maxn 1000004
#define OK 0
#define REPEAT 1
#define WRONG 2
int trie[maxn][30];
int mrk[maxn];
int sum[maxn];     // 判断点名点了多少次
int n,m;
string s;
 int top=0;
void init(){
    for(int i = 0;i<maxn;++i){
        for(int j=0;j<30;++j){
            trie[i][j]=0;
        }
        mrk[i]=0;
        sum[i]=0;
    }
}
void trie_init(string str){
     int l=str.length();

     int now=0;
    
     for(int i = 0;i<l;++i){
         int c=str[i]-'a'+1;
         if(trie[now][c]==0){
            trie[now][c]=++top;
         }
         now=trie[now][c];
     }
     mrk[now]=1;  // 标记这是一个人的名字
}

int trie_check(string str){
    int l=str.length();
    int now=0;
    for(int i = 0;i<l;++i){
       int c=str[i]-'a'+1;
       if(trie[now][c]==0){
           return WRONG;
       }
       now=trie[now][c];
    }
    
    if(mrk[now]!=1){
        return WRONG;
    }
    if(sum[now]==0){
        sum[now]=1;
        return OK;
    }else{
        return REPEAT;
    }
     

    
}
int main(){
    //freopen("test/A.in","r",stdin);
    init();     // 初始化
    cin>>n;
    // 初始化树
    for(int i =0;i<n;++i){
        cin>>s;
        trie_init(s);
    }
    cin>>m;
    for(int i = 0;i<m;++i){
        cin>>s;
        int ans;
        ans=trie_check(s);
        if(ans==OK){
            cout<<"OK"<<endl;
        }else if(ans==REPEAT){
            cout<<"REPEAT"<<endl;
        }else{
            cout<<"WRONG"<<endl;
        }
        
    }

}
#include<iostream>
#include<vector>
using namespace std;
#define maxn 400004
vector<int> mrk[maxn];  // 用vetor      // 不用wector可以把你卡死
int trie[maxn][27];     // 标记在哪里出现过
int top=0;
int n,m,l;

void init(){
     for(int i = 0;i<maxn;++i){
         for(int j = 0;j<27;++j){
             trie[i][j]=0;
         }
     }
     top=0;
}

// index是出现在那个段落
void trie_init(string str,int index){
      int now=0;
      int l=str.length();
      for(int i =0;i<l;++i){
         int c=str[i]-'a';
         if(trie[now][c]==0){
             trie[now][c]=++top;
         }
         now=trie[now][c];
      }
      // 看看要不要标记
      int i=mrk[now].size();
      if(i!=0&&mrk[now][i-1]==index){
          return;
      }else{
         mrk[now].push_back(index); 
      }
}


void trie_check(string str){
    int l=str.length();
    int now=0;
    for(int i = 0;i<l;++i){
        int c=str[i]-'a';
        if(trie[now][c]==0){
            cout<<endl;
            return;
        }
        now=trie[now][c];
    }
     
    int Size=mrk[now].size();
    if(Size==0){
        cout<<endl;
        return;
    }
    for(int i = 0;i<Size;++i){
        if(i==Size-1){
            cout<<mrk[now][i]<<endl;
        }else{
            cout<<mrk[now][i]<<" ";
        }
    }

}
int main(){
    //freopen("test/A.in","r",stdin);
    init();
    cin>>n;
    string s;
    // 扔进树里
    for(int i = 1;i<=n;++i){
        cin>>l;
        for(int j=0;j<l;++j){
            cin>>s;
            trie_init(s,i);
        }
    }
    cin>>m;
    for(int i = 0;i<m;++i){
        cin>>s;
        trie_check(s);
    }
}
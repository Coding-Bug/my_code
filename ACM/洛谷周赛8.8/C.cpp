#include<iostream>
using namespace std;
#define maxn 100000
#define maxc 128
int mrk[maxn];
int trie[maxn][maxc];
long long ans=0;
int top=0;
void init(){
    for(int i = 0;i<maxn;++i){
        mrk[i]=0;
    }
    for(int i = 0;i<maxn;++i){
        for(int j = 0;j<maxc;++j){
            trie[i][j]=0;
        }
    }
    mrk[0]=1;
}

void trie_init(string s){
    int now=0;
    int l=s.length();
    for(int i = 0,c;i<l;++i){
        c=s[i]-'/';
        if(trie[now][c]==0){   
           trie[now][c]=++top;
        }
        if(i<l-1&&s[i]=='/'){
            if(mrk[now]!=1){
                //cout<<'*'<<now<<endl;
                ans++;
                mrk[now]=1;
            }
        }
        now=trie[now][c];
    }
    if(mrk[now]!=1){
        //cout<<"**"<<now<<endl;
        ans++;
        mrk[now]=1;
    }
}
int main(){
    init();
    //freopen("test/A.in","r",stdin);
    string s;
    int n=0;
    cin>>n;
   
    for(int i = 0;i<n;++i){
        cin>>s;
        trie_init(s);
        cout<<ans<<endl;
    }
    
}
#include<iostream>
using namespace std;
#define maxn 500005
int trie[maxn][2];
int top=0;
int mrk[maxn];
int sum[maxn];     // 记录每个结点下面的结点个数
int pre[maxn];     // 记录每个结点的父亲
int s[maxn];

int m,n;

void init(){
    for(int i = 0;i<maxn;++i){
        for(int j = 0;j<2;++j){
            trie[i][j]=0;
        }
        mrk[i]=0;
        sum[i]=0;
        pre[i]=0;
    }
    top=0;
}


void trie_init(int* str,int l){
     int now=0;
     for(int i=0;i<l;++i){
         int c=str[i];
         if(trie[now][c]==0){
            trie[now][c]=++top;
         }
         pre[trie[now][c]]=now;
         now=trie[now][c];
     }
     mrk[now]++;     // 现在是记录有多少了   
     // 更新结点的数量
    //  while(now!=0){
    //      sum[now]=sum[trie[now][0]]+sum[trie[now][1]]+mrk[now];
    //      now=pre[now];
    //  }
    while(now!=0){
        sum[now]++;
        now=pre[now];
    }
}

int trie_check(int* str,int l){
    int now=0;
    int ans=0;
    for(int i = 0;i<l;++i){
        int c=str[i];
        
        if(trie[now][c]==0){
           return ans;      // 找完了
        }
        now=trie[now][c];   // 往下走
        // 找到一些是它的前缀
        if(mrk[now]!=0){
          ans+=mrk[now];
        }
    }
    
    // 加上是别人的前缀
    ans+=sum[now]-mrk[now];    // 因为sum[now]有mrk[now]；
    return ans;

}

int main(){
    //freopen("test/A.in","r",stdin);
    init();
    cin>>m>>n;
    int k=0;
    int ans=0;
    // 将输入全部丢进树中
    for(int i = 0;i<m;++i){
       cin>>k;
       for(int i=0;i<k;++i){
           cin>>s[i];
       }
       trie_init(s,k);
    }
    
    // for(int i = 0;i<10;++i){
    //     cout<<i<<" "<<sum[i]<<endl;
    // }
    // exit(1);

    for(int i =0;i<n;++i){
        cin>>k;
        for(int i=0;i<k;++i){
           cin>>s[i];
        }
        ans=trie_check(s,k);
        cout<<ans<<endl;
    }
}
#include<iostream>
using namespace std;
#define maxn 1000006 
#define ll long long
int mrk[maxn]; 
ll Xor[maxn];     // 记录根节点到这个结点的异或值  
int trie[maxn][2];
int n;
int top=0;
ll Ans=0;
ll MAX=0;
int l=0;     // 异或后数子最高的那位
void init(){
    for(int i = 0;i<maxn;++i){
        mrk[maxn]=0;
        Xor[i]=0;
        trie[i][0]=0;
        trie[i][1]=0;
    }

}
// 用这些根节点到某个结点的异或值建树
void trie_init(ll w){
    int now=0;
     // 从高位开始建01trie
     for(int i = l-1;i>=0;--i){ 
        int c=((w&(1<<i))&&1);
        //cout<<now<<" "<<c<<" "<<trie[now][c]<<" ";
        if(trie[now][c]==0){
           trie[now][c]=++top;
        }
        //cout<<top<<endl;
        
        now=trie[now][c];
     }
}

// 用这个点去匹配另一个点，让异或值尽可能大
void trie_chect(ll w){
    int now=0;
    ll ans=0;
    for(int i = l-1;i>=0;--i){
        int c=((w&(1<<i))&&1);      // 记录当当前位
        
        if(c==0){     // 如果c为0，那么要找1
           if(trie[now][1]!=0){
              now=trie[now][1];
              ans+=(1<<i);
              
              //cout<<l<<" "<<ans<<endl;
            }else{
              now=trie[now][0];
            }
        }else{
            if(trie[now][0]!=0){
              now=trie[now][0];
              ans+=(1<<i);
            }else{
              now=trie[now][1];
            }
        }
        //cout<<ans<<endl;
    }
    Ans=max(ans,Ans);

}


int main(){
    init();
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i = 1;i<=n;++i){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        Xor[v]=Xor[u]^w;
        MAX=max(Xor[v],MAX);    // 记录异或的最大值
    }
    // for(int i = 1;i<=n;++i){
    //     cout<<i<<" "<<Xor[i]<<endl;
    // }
    while(MAX!=0){
        MAX=MAX>>1;
        //cout<<MAX<<endl;
        l++;
    }
    //cout<<l<<endl;

    //cout<<"jj"<<endl;
    // 将那些到根节点的异或值扔进树种
    for(int i =1;i<=n;++i){
        trie_init(Xor[i]);
    }
    // cout<<trie[6][0]<<endl;
    // cout<<top<<endl;
    for(int i = 1;i<=n;++i){
        trie_chect(Xor[i]);
    }

    cout<<Ans<<endl;

}
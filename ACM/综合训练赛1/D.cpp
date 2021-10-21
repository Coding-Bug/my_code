#include<iostream>
using namespace std;
#define maxn 200000


int trie[maxn][2]={0};
int top=0;
int mrk[maxn]={0};
int a[maxn];
int pre[maxn]={0};
int sum[maxn]={0};   // 这个点后面后多少
int ans=0;
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
void trie_init(int s[],int n){
    int now=0;
    for(int i = 0;i<n;++i){
       int c=s[i];
       if(trie[now][c]==0){
           trie[now][c]=++top;
       }
       
       pre[trie[now][c]]=now;
       now=trie[now][c];
    }

    mrk[now]++;
    while(now!=0){
        sum[now]++;
        now=pre[now];
    }


}
void trie_check(int s[],int n){
    int now=0;
    for(int i = 0;i<n;++i){
       int c=s[i];
       if(trie[now][c]==0){
           return;
       }
       now=trie[now][c]; 
       ans+=mrk[now];
    }

    ans+=sum[now]-mrk[now];
}

int main(){
    int m,n;
    init();
    //freopen("test/A.in","r",stdin);
    scanf("%d%d",&m,&n);
    // 生成
    for(int i = 0;i<m;++i){
        int b=0;
        scanf("%d",&b);
        for(int j = 0;j<b;++j){
            scanf("%d",&a[j]);
        }
        trie_init(a,b);
    }

    for(int i = 0;i<n;++i){
        int b=0;
        scanf("%d",&b);
        for(int j = 0;j<b;++j){
            scanf("%d",&a[j]);
        }
        ans=0;
        trie_check(a,b);
        printf("%d\n",ans);
    }




}


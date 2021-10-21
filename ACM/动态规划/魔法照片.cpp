#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 20005

typedef struct Node
{
    int pos;
    int w;
}Node;

bool cmp(Node a,Node b){
    if(a.w==b.w){
        return a.pos<b.pos;
    }
    else return a.w>b.w;
}

bool cmp1(Node a,Node b){
    if(a.w==b.w){
        return a.pos<b.pos;
    }
    return a.w>b.w;
}
Node node[maxn];
int E[12];
int n,k;

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    for(int i = 1;i<=10;++i){
        cin>>E[i];
    }

    // 初始权值和编号
    for(int i = 1;i<=n;++i){
        cin>>node[i].w;
        node[i].pos=i;
    }
    
    sort(node+1,node+1+n,cmp1);
    
    for(int i = 1;i<=n;++i){
        node[i].w+=E[(i-1)%10+1];
    }

    node[0].w=-1;
    sort(node,node+n+1,cmp);
    for(int i = 0;i<k-1;++i){
        cout<<node[i].pos<<" ";
    }
    cout<<node[k-1].pos<<endl;
}
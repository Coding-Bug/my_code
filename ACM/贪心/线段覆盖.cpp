#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 1000005
typedef struct Node
{
    int a;
    int b;
}Node;
bool cmp(Node a,Node b){
    if(a.b==b.b){
        return a.a>b.a;
    }
    return a.b<b.b;
}
Node node[maxn];
int main(){
    int n;
    cin>>n;
    for(int i =0;i<n;++i){
        cin>>node[i].a>>node[i].b;
    }
    sort(node,node+n,cmp);
    int ans=0;
    int now=0;
    for(int i = 0;i<n;++i){
        if(now<=node[i].a){
            ans++;
            now=node[i].b;
        }
    }
    cout<<ans<<endl;

}

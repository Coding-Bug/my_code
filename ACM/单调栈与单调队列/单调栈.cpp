#include<iostream>
#include<stack>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0)
#define maxn 3000004
int n;
int f[maxn];
typedef struct Node{
     int a;
     int pos;
}Node;
Node node[maxn];
int main(){
    TLE;
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i = 1;i<=n;++i){
        cin>>node[i].a;
        node[i].pos=i;
        f[i]=0;
    }
    stack<Node> Q;
    for(int i = 1;i<=n;++i){
       if(Q.empty()){
           Q.push(node[i]);
       }else{
           while(!Q.empty()&&Q.top().a<node[i].a){
                 Node p=Q.top();
                 Q.pop();
                 f[p.pos]=node[i].pos;
           }
           Q.push(node[i]);
       }
    }
    for(int i =1;i<=n;++i){
        cout<<f[i]<<" ";
    }
    cout<<endl;


}
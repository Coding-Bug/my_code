#include<iostream>
#include<queue>
using namespace std;
#define ll long long
#define maxn 10004
typedef struct Node{
     int val;
     bool operator <(const Node &a) const{
         return val>a.val;
     }
}Node;
Node node[maxn];
int n,m;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m;
    for(int i = 1;i<=n;++i){
        cin>>node[i].val;
    }
    priority_queue<Node> Q;
    int i = 1;
    while(i<=m&&i<=n){
        Q.push(node[i++]);
    }
    ll ans=0;
    Node temp[maxn];
    while(!Q.empty()){
        Node p=Q.top();
        Q.pop();
        int w=p.val;    // 花费的时间
        //cout<<w<<endl;
        ans+=w;
        int cnt=0;      // 有几个还没做完的
        while(!Q.empty()){
            p=Q.top();
            Q.pop();
            if(p.val>w){
                p.val-=w;
                temp[cnt++]=p;
                
            }
        }
        // 没做完的push回去
        for(int j=0;j<cnt;++j){
            //cout<<temp[j].val<<" ";
            Q.push(temp[j]);
        }
        //int k=cnt;
         //cout<<endl;
        // 看看还能push多少
        while(cnt<m&&i<=n){
            //cout<<node[i].val<<" ";
            Q.push(node[i++]);
            cnt++;
        }
        //cout<<endl;
    }
    cout<<ans<<endl;




}
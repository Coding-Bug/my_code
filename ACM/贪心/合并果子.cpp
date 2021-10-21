#include<iostream>
#include<queue>
using namespace std;
#define ll long long
#define maxn 10004

typedef struct Node
{
    ll val;
    bool operator <(const Node &b )const{
        return val>b.val;
    }
}Node;
Node a[maxn];

int main(){
    //freopen("test/b.in","r",stdin);
    priority_queue<Node> Q;
    ll n;
    cin>>n;
    for(int i = 0;i<n;++i){
        cin>>a[i].val;
        Q.push(a[i]);
    }

    ll pl=0;
    ll pr=n-1;
    ll ans=0;
    while(!Q.empty()){
        ll temp=0;
        Node p=Q.top();
        Q.pop();
        temp+=p.val;
        if(Q.empty()){
            break;
        }
        p=Q.top();
        Q.pop();
        temp+=p.val;
        ans+=temp;
        p.val=temp;
        Q.push(p);
    }
    cout<<ans<<endl;

}
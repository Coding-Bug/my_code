#include<iostream>
#include<stack>
#define TLE ios::sync_with_stdio(0),cin.tie(0);
using namespace std;
#define maxn 100004
int n;
int f[maxn];
typedef struct Node{
     int a;
     int pos;
}Node;
Node node[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    while(n!=0){
        for(int i = 1;i<=n;++i){
            cin>>node[i].a;
            node[i].pos=i;
            f[i]=0;
        }

        // 两边要做好
        node[n+1].pos=n+1;
        node[n+1].a=0;
        node[0].a=0;
        node[0].pos=0;

        // 向右边拓展，找到第一个比他小的
        stack<Node> Q1;
        for(int i = 1;i<=n+1;++i){
           if(Q1.empty()){
               Q1.push(node[i]);
           }else{
               while(!Q1.empty()&&Q1.top().a>node[i].a){
                   Node p=Q1.top();
                   Q1.pop();
                   f[p.pos]=node[i].pos-p.pos;   // 我们求的是拓展长度
               }
               Q1.push(node[i]);
           }
        }


        // 向左边也来一遍
        stack<Node> Q2;
        for(int i = n;i>=0;--i){
           if(Q2.empty()){
               Q2.push(node[i]);
           }else{
               while(!Q2.empty()&&Q1.top().a>node[i].a){
                   Node p=Q1.top();
                   Q1.pop();
                   f[p.pos]+=p.pos-node[i].pos;   // 我们求的是拓展长度
               }
               Q1.push(node[i]);
           }
        }
        int ans=0;

        for(int i = 1;i<=n;++i){
            int temp=node[i].a*(f[i]-1);    // 注意减一，因为上面多算了
            if(temp>ans){
                ans=temp;
            }
        }
        cout<<ans<<endl;
        cin>>n; 
    }
}
#include<iostream>
#include<stack>
#include<algorithm>
#define TLE ios::sync_with_stdio(0),cin.tie(0)
using namespace std;
#define MAX 1000004
unsigned long long mod=0xffffffffffffffff;


// 创建a的结构体
typedef struct Node
{
    int x;   // a的值
    int pos; // 入队位置
}Node;

bool cmp1(Node a,Node b){
    return a.x<b.x;
}
bool cmp2(long long a,long long b){
    return a<b;
}
bool cmp3(long long a, long long b){
    return a>b;
}
long long sum[MAX];   // 存放所需要增加的次数
long long b[MAX];
Node a[MAX];
unsigned long long ans=0;
int n;
int main(){
    TLE;
    //freopen("test/F.txt","r",stdin);
    cin>>n;
    for(int i = 0;i<n;++i){
        cin>>a[i].x;
    }
    for(int i = 0;i<n;++i){
        cin>>b[i];
    }
    sort(a,a+n,cmp1);
    sort(b,b+n,cmp2);
    stack<Node> STK;   // 存放结点的栈
    int nn=0;    // 需要变动的结点数
    int i=0;
    for(long long j = 1;j<1e9;++j){
        if(STK.empty()&&j<a[i].x){    // 枚举到这个位置的时候栈为空，j直接跳到a[i];
            j=a[i].x;      // 直接让j跳到a[i];
        }
        while(i<n&&a[i].x<=j){
            a[i].pos=j;   // 进栈位置
            STK.push(a[i]);
            i++;
        }
        if(!STK.empty() ){
           Node p=STK.top();    // 出一个结点放到这个位置
           STK.pop();
           if(p.pos-j==0){   // 如果不用变，则继续
            ;
           }
           else{
           sum[nn++]=j-p.pos;  // 记录代价
            }
        }
        if(i==n&&STK.empty()){  // 放完了
            break;
        }
    }
    // 将sum从大到小排
    sort(sum,sum+nn,cmp3);
    // for(int i = 0;i<nn;++i){
    //     cout<<sum[i]<<" ";
    // }
    // cout<<endl;
    for(i = 0;i<nn;++i){
       ans=ans%mod+(sum[i]%mod)*(b[i]%mod);
       ans=ans%mod;
    }
    cout<<ans<<endl;


}
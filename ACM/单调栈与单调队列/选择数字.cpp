#include<iostream>
using namespace std;
#define maxn 100005

long long a[maxn];
long long q[maxn];
long long dp[maxn];   // dp[i]为前i个数符合条件并且把自己也删除之后使得和最小
int head;
int tail;
long long sum=0; // 保存全部和
int n,k;

void fun(){
    head=tail=0;
    // 不能连续超过k个选择，所以k个可以选，所以可以前k个不删，所以dp[k+1]=k+1
    for(int i = 1;i<=k+1;++i){
       dp[i]=a[i];          // 前k个数都只需要删除自己就可以，所以各自的dp都是自己本身
    }
    // 维护从第i个数前k个选了之后得到的和最小值
    // 维和玩后队列中就是一个升序的队列，并且队尾是前k个的最小值
    for(int i=1;i<=k+1;++i){
        // 队列的队头是大的，所以从队头出队
        while(head!=tail&&dp[q[head-1]]>dp[i]){   // 注意是head-1
            head--;
        }
        q[head++]=i;  
    }

    for(int i=k+2;i<=n;++i){
        // 先算出dp[i]
        dp[i]=dp[q[tail]]+a[i];
        // 用这个dp[i]更新队列，因为它会是下一个元素的前k个
        while(head!=tail&&dp[q[head-1]]>dp[i]){   
            head--;
        }
        // 将队列中，比第i个元素前k个还要前的元素出队，因为第i个只能由前k+1个转移过来
        // 但并不是每次队尾的元素都是比i元素前k+1个还要前，所以要判断
        while(head!=tail&&q[tail]<=i-k-1){    
            tail++;
        }
        // 第i个入队
        q[head++]=i;
    }
    // 后面k个的最小值就是要减去的和
    cout<<sum-dp[q[tail]]<<endl;
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    
    for(int i = 1;i<=n;++i){
        cin>>a[i];
        sum+=a[i];
    }
    fun();
    return 0;

    
}
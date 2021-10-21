#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
long long  T;
long long n;
typedef struct ELE{
long long a;
long long b;
long long c;
long long d;
}Ele;

// 重写力量小根堆
typedef struct cmp1{
    bool operator () (Ele a,Ele b){
        if(a.a==b.a){
            return a.b>b.b;
        }
        return a.a>b.a;
    }
}cmp1;

// 重写智慧小根堆
typedef struct cmp2{
    bool operator()(Ele a,Ele b){
        return a.b>b.b;
    }
}cmp2;
Ele ele[100004];
long long ans1=0;
long long sum1=0;
long long ans2=0;
long long sum2=0;   // 记录当前精神的和
int main(){
    //freopen("test/A.txt","r",stdin);
    cin>>T;
    cin>>n;
    priority_queue<Ele,vector<Ele>,cmp1> Q1 ;  // 力量从小到大的小根堆
    priority_queue<Ele,vector<Ele>,cmp2> Q2;  // 精神从小到大的小根堆
    for(int i =0;i<n;++i){
        cin>>ele[i].a>>ele[i].b>>ele[i].c>>ele[i].d;
        Q1.push(ele[i]); 
    }
    // for(int i = 0;i<n;++i){
    //     cout<<Q1.top().a<<" "<<Q1.top().b<<endl;
    //     Q1.pop();
    // }
    // cout<<endl;
    // for(int i = 0;i<n;++i){
    //     cout<<Q2.top().a<<" "<<Q2.top().b<<endl;
    //     Q2.pop();
    // }
    // cout<<endl;
    
    // 求出最小的力量值
    while(!Q1.empty()){
       Ele p=Q1.top();
       Q1.pop();
       if(sum1>=p.a){// 当前的力量够穿
          sum1+=p.c;
          continue;
       }else{   // 不够穿的时候要更新初始值
          ans1+=p.a-sum1;
          sum1=p.a+p.c;
       }
    }

    // Q1还要用
    for(int i = 0;i<n;++i){
        Q1.push(ele[i]);
    }

    long long beg=ans1;  // 记录最小初始力量
    // 在力量最小值开始满足的情况下，争取精神最小
    while(!Q1.empty()||!Q2.empty()){   // 全部选完之后两个队列都为空
         Ele p;
        // 选出当前力量值下Q1中所有可取装备 
        while(!Q1.empty()){ 
            if(beg<Q1.top().a){  
                break;
            }
            // 可以穿的放到Q2,但是这里害不能穿
            p=Q1.top();
            Q2.push(p);
            Q1.pop();
        }
        // 尝试穿一件
        if(!Q2.empty()){
        p=Q2.top();
        Q2.pop();
        if(sum2>=p.b){ // 当前精神值够穿
            sum2+=p.d;
        }else{
            ans2+=p.b-sum2;
            sum2+=p.b-sum2+p.d;
        }
        beg+=p.c;  // 选了之后要加上力量
        }
    }
    cout<<ans1<<" "<<ans2<<endl;
    
    
}
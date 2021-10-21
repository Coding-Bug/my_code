#include<iostream>
#include<vector>
#include<algorithm>
#define maxn 1004
using namespace std;
#define ll long long
typedef struct{
    ll  a;
    ll  b;
}Node;
bool cmp(Node a,Node b){
     return a.a*a.b<b.a*b.b;
}
vector<int> LintoH(ll a){
    vector<int> ans;
    while(a!=0){
        ans.push_back(a%10);
        a/=10;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

void print(vector<int> a){
    for(int i = 0;i<a.size();++i){
        cout<<a[i];
    }
}

int cmp1(vector<int> a,vector<int> b){
    // 长度不等
    if(a.size()!=b.size()){
        return a.size()>b.size()?1:-1;
    }
    // 长度相同的时候,vector有比较的功能
    if(a>b){
        return 1;
    }else if(a<b){
        return -1;
    }else{
        return 0;
    }
}

vector<int> HmulL(vector<int> a,ll b){
    vector<int> ans;
    reverse(a.begin(),a.end());
    ll C=0;
    for(int i = 0;i<a.size()||C!=0;++i){
        // 如果a还有
        if(i<a.size()){
            C+=a[i]*b;
        }
        ans.push_back(C%10);
        C/=10;   // 这些多余的留着后面一直进位上去即可
    }
    while(ans.size()>1&&ans.back()==0){
        ans.pop_back();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

vector<int> HdivL(vector<int> a,ll b,ll &r){
    vector<int> ans;
    ll ret=0;    // 余数    
    for(int i = 0;i<a.size();++i){
        ret=ret*10+a[i];
        ans.push_back(ret / b);
        ret=ret%b;
    }
    r=ret;   // 最后剩下余数
    // 反转
    reverse(ans.begin(),ans.end());
    // 去掉前缀0
    while(ans.size()>1&&ans.back()==0){
        ans.pop_back();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}


int n;
ll x,y;
Node node[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i = 0;i<=n;++i){
        cin>>node[i].a>>node[i].b;
    }
    sort(node+1,node+1+n,cmp);
    vector<int> Sum;   // 前面的全部相乘
    Sum=LintoH(node[0].a);
    vector<int> Ans;
    Ans=LintoH(0);
    vector<int> temp;
    ll r;
    for(int i =1;i<=n;++i){
        temp=HdivL(Sum,node[i].b,r);
        //print(Sum);cout<<" "<<node[i].b<<" ";print(temp);cout<<endl;
        Sum=HmulL(Sum,node[i].a);
        if(cmp1(temp,Ans)==1){
            Ans=temp;
        }
    }
    print(Ans);
}
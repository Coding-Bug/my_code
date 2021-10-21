#include<iostream>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;

void print(vector<int> a){
    for(int i = 0;i<a.size();++i){
        cout<<a[i];
    }
}
vector<int> HaddH(vector<int> a,vector<int> b){
    int alen=a.size();
    int blen=b.size();
    
    // 保持a比b大
    if(alen < blen){
        return HaddH(b,a);
    }
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    vector<int> ans;  // 存结果
    int C=0;     // 每一位相加的结果
    for(int i = 0;i<alen;++i){
        C += a[i];
        // 如果b在该位还有，就加上b
        if(i < blen){
           C += b[i];
        }
        ans.push_back(C % 10);
        C/=10;
    }
    if(C!=0){ // 后面还有进位，不会超过10，直接puss即可
    ans.push_back(C);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}


vector<int> HsubH(vector<int> a, vector<int> b){
    // 先将字符串反转
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    vector<int> ans;
    int alen=a.size();
    int blen=b.size();
    int C=0;
    for(int i = 0;i < alen;++i){
        C=a[i]-C;  // 减去借
        if(i < blen){
            C-=b[i];  // b该位还有就减掉
        }
        // 不够减
        if(C < 0){
            ans.push_back(C+10);
            C = 1;
        }else{
            ans.push_back(C);
            C = 0;
        }
    }
    // 去掉前缀0,注意不能删到长度为0,0是可以有的
    while(ans.size()>1&&ans.back()==0){
        ans.pop_back();
    }
    reverse(ans.begin(),ans.end());
    
    return ans;
}



//高精度乘低精度
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
    // 去前缀0
    while(ans.size()>1&&ans.back()==0){
        ans.pop_back();
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

// 高精度除以低精度
// r是余数
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

// 低精度转换成高精度
vector<int> LintoH(ll a){
    vector<int> ans;
    while(a!=0){
        ans.push_back(a%10);
        a/=10;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

int cmp(vector<int> a,vector<int> b){
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

// 高精度乘以高精度
vector<int> HmulH(vector<int> a,vector<int> b){
    vector<int> ans;
    vector<int> C;
    ans.push_back(0);
    reverse(b.begin(),b.end());  // b当被乘数，b使低位在前即可反转即可 
    int blen=b.size();
    for(int i=0;i<blen;++i){
        C=HmulL(a,b[i]);     // 将被乘数的一位与乘数相乘
        ans=HaddH(ans,C);   // 答案加上相乘的结果
        a.insert(a.end(),0);   // 实现乘数乘以10
    }
    // 后面得到的ans就是高位低存的，不用反转
    return ans;
}



using namespace std;
int main(){
    vector<int> a;
    vector<int> b;
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);

    b.push_back(1);
    b.push_back(0);
    b.push_back(0);
    ll k=8;
    ll r=0;
    print(a);cout<<" + ";print(b);cout<<" = ";print(HaddH(a,b));cout<<endl;
    print(a);cout<<" - ";print(b);cout<<" = ";print(HsubH(a,b));cout<<endl;
    cout<<k<<" * ";print(a);cout<<" = ";print(HmulL(a,k));cout<<endl;
    print(a);cout<<" / ";cout<<k;cout<<" = ";print(HdivL(a,k,r));cout<<endl;
    print(b);cout<<" "<<cmp(b,a)<<" ";print(a);cout<<endl;

    ll m=243243240;
    cout<<m<<" -> ";print(LintoH(m));cout<<endl;
    print(b);cout<<" * ";print(a);cout<<" = ";print(HmulH(a,b));cout<<endl;
    
    
}

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
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
int main(){
    vector<int> f[3];
    f[0]=LintoH(1);
    f[1]=LintoH(2);
    int n;
    cin>>n;
    for(int i = 2;i<=n;++i){
        f[i%3]=HaddH(f[(i-1)%3],f[(i-2)%3]);
    }
    if(n==0){
      cout<<0<<endl;
      return 0;
    }
    print(f[(n-1)%3]);

}
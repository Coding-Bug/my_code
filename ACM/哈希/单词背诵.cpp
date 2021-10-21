#include<iostream>
#include<unordered_map>
#include<cstring>
#include<vector>
using namespace std;
#define ll long long
#define maxn 1004
#define maxm 100004 
#define maxlen 12

unordered_map<string,ll> mp1;
unordered_map<string,ll> mp2;
string p;
vector<string> str;
int n,m;
ll ans1=0;   // 第一个答案
int ans2=1e9;



int main(){
    //freopen("test/A.in","r",stdin);
    
    cin>>n;
    // 先存将要学的存
    for(int i=0;i<n;++i){
        cin>>p;
        mp1[p]=1;
    }
    cin>>m;
    for(int i =0;i<m;++i){
        cin>>p;
        str.push_back(p);
        if(mp1[p]!=0&&mp2[p]==0){
          ans1++;
        }
        mp2[p]++;
    }
    cout<<ans1<<endl;
    if(ans1==0){
        cout<<0<<endl;
        return 0;
    }

    // 求第二个

    mp2.clear();    // mp2记录当前区间l-r内，各种字符串的数
    int cnt=0;     // 当前区间内字符种树，是在mp1中的
    
    // 枚举左端点
    int r=-1;
    for (int l = 0;l<m;++l){
        while(r<m-1&&cnt<ans1){
              r++;
             // 判断r
             if(mp1[str[r]]!=0){
                 if(mp2[str[r]]==0){
                    cnt++;
                 }
                mp2[str[r]]++;
             }
             
           
        }
        // 如果上面走的r找到了一个
        // 更新最短长度
        if (cnt==ans1){
            ans2=min(ans2,r-l+1);
        }
        // l向前移动，l当前的字符在l-r中数量减一
        if(mp1[str[l]]!=0){
            mp2[str[l]]--;
            if(mp2[str[l]]==0){
                cnt--;
            }
        }
        
    }
    
    cout<<ans2<<endl;
}
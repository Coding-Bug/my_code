// 进行字母代换
#include<iostream>
using namespace std;
string standar_str="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string my_str=     "TBEDCMGHOJKLFNIPQRSAUVWXYZ";    
//string my_str=     "TBEDCFGHOJKLMNIPQRSAUVWXYZ";
  
string str;         // 原字符串
string ans_str;     // 答案串
char change[256];   // 字母映射表

int main(){
    freopen("test/str.in","r",stdin);
    freopen("test/a.out","w",stdout);
    cin>>str;
    // 构建字母代换表
    for(auto i = 0;i<26;++i){
       change[my_str[i]]=standar_str[i];
    }
    for(int i=0;i<str.length();++i){
      char temp=change[(int)(str[i])];
      ans_str.push_back(temp);
    }
    cout<<str<<endl;
    cout<<ans_str<<endl;
}
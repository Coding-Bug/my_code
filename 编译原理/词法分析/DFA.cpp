#include<iostream>
#include<cstring>
#include<map>
using namespace std;
#define maxn 1000
map<char,int> valid; 
char state[maxn]; // 状态
map<pair<char,char>, char> mp;  // 映射

int main(){
    //freopen("test/A.txt","r",stdin);
    char c;
    char str[maxn];
    // 有效字符
    c=getchar();
    while(c!='#'){
        valid[c]=1;
        c=getchar();// 接受空格
        if(c=='#'){
            break;
        }
        c=getchar();
    }
    c=getchar();

    // 所有状态(没用)
    cin.getline(str,maxn,'\n');

    // DFA
    cin.getline(str,maxn,'\n');


    while(strlen(str)!=0){
        int len=strlen(str);
        for(int i = 2;i<len;i+=7){
            pair<char,char> p(str[i],str[i+2]);
            mp[p]=str[i+5];
        }
        cin.getline(str,maxn,'\n');
    }

    //读入输入串，边读入边分析 
    cin.getline(str,maxn,'\n');
    while(strlen(str)!=0){
        bool flag=true;  // pass标记
        char now='X';    // 标记状态
        int len=strlen(str);
        for(int i=0;i<len-1;++i){
            pair<char,char> p(now,str[i]);
            if(valid[str[i]]!=1||mp[p]==0){
                cout<<"error"<<endl;    
                flag=false;
                break;
            }
            cout<<str[i]<<endl;
            now=mp[p];
        }
        cin.getline(str,maxn,'\n');
        if(!flag){
            continue;
        }
        if(now!='Y'){
            cout<<"error"<<endl;
            continue;
        }
        cout<<"pass"<<endl;
    }





    
}
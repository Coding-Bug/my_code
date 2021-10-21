#include<iostream>
#include<cstring>
#include<unordered_map>
using namespace std;
#define maxn 200000
unordered_map<string,int> cnt;
unordered_map<string,int> vis;

int n;
string s;
char str[maxn+2];
int ans=0;
int main(){
    //freopen("test/A.in","r",stdin);
    memset(str,'\0',sizeof(str));
    cin>>n;
    char c='1'; 
    for(int i = 0;i<n;++i){
        cin>>s;
        for( int j = 0; j < s.size(); j++ )
        {
        s[j] = tolower(s[j]);
        }
        //cout<<s<<endl;
        // 存入哈希中
        cnt[s]=1;
        // 清空s
        s.clear();
        
    }


    // 搜索文本
    getchar();
    cin.getline(str,maxn,'\n');
    //cout<<str<<endl;
    int i=0;
    while(str[i]!='\0'){
         bool flag=false; //有没有接受单词
         c=str[i];
         if(c=='\0'){
             break;
         }
         while(c!=' '&&c!=','&&c!='.'){
             if(c<='Z'&&c>='A'){
                c=tolower(c);
             }
             if(c=='\0'){
             break;
             }
              s.push_back(c);
              c=str[++i];
              flag=true;
         }
         if(c=='\0'){
             break;
         }
         //cout<<s<<endl;
         if(flag){
            if(vis[s]!=1){
                vis[s]=1;
                if(cnt[s]==1){
                    ans++;
                }
            }
         }
         if(c=='.'){
             vis.clear();
         }
         s.clear();
         ++i;
    }
    cout<<ans<<endl;

}
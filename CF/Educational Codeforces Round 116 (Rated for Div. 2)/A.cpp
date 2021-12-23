#include<iostream>
#include<cstring>
using namespace std;
#define maxn 110
char str[maxn];
int pos_ab[maxn]; 
int pos_ba[maxn]; 
bool is_ba[maxn];
bool is_ab[maxn];
int num_ab=0;
int num_ba=0;
int t;
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        
        memset(pos_ba,0,sizeof(pos_ba));
        memset(pos_ab,0,sizeof(pos_ab));
        memset(is_ba,false,sizeof(is_ba));
        memset(is_ab,false,sizeof(is_ab));
        num_ab=0;
        num_ba=0;
        cin>>str;
        int len=strlen(str);
        if(len==1){
            cout<<str<<endl;
            continue;
        }
        // 记录ab和ba出现的数量和位置
        for(int i=1;i<len;++i){
            if(str[i]=='b'&&str[i-1]=='a'){
                pos_ab[num_ab++]=i;
                is_ab[i]=true;
                is_ab[i-1]=true;
            }else if(str[i]=='a'&&str[i-1]=='b'){
                pos_ba[num_ba++]=i;
                is_ba[i]=true;
                is_ba[i-1]=true;
            }
        }
        if(num_ba==num_ab){
            cout<<str<<endl;
            continue;
        }

        // ab多，减去ab
        if(num_ab>num_ba){
            int k = num_ab-num_ba;   // 需要减去的ab
            for(int i =0;i<num_ab;++i){
                if(k==0){
                    break;
                }
                if(!is_ba[i]){
                    str[i]=str[i]=='a'?'b':'a';
                    k--;
                }
            }

        }
        if(num_ba>num_ab){
            int k = num_ba-num_ab;   // 需要减去的ab
            for(int i =0;i<num_ba;++i){
                if(k==0){
                    break;
                }
                if(!is_ab[i]){
                    str[i]=str[i]=='a'?'b':'a';
                    k--;
                }
            }

        }
        cout<<str<<endl;



    }
}
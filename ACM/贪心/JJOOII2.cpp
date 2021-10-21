#include<iostream>
using namespace std;
#define maxn 200004
int J[maxn],O[maxn],I[maxn];
int cntj=0;
int cnto=0;
int cnti=0;
int ans=1e9;
int main(){
    //freopen("test/A.in","r",stdin);
    string str;
    int n,k;
    cin>>n>>k;
    getchar();
    cin>>str;
    n=str.size();
    // 放到桶里
    for(int i = 0;i<n;++i){
        if(str[i]=='J'){
            J[cntj++]=i;
        }
        if(str[i]=='O'){
            O[cnto++]=i;
        }
        if(str[i]=='I'){
            I[cnti++]=i;
        }
    }
    int nj=0;   // j结束的位置
    int po=0;   // o开始的位置
    int no=0;
    int pi=0;
    int ni=0;
    bool flag=true;   // 是否还能找
    // J只需要从头遍历一遍，O和I是跟着j走的，O和I一定是越往前取越好，所以O和I不是全遍历
    for(int i =0;i<cntj;++i){
        // k不够了
        if(cntj-i<k){
            break;
        }
        nj=i+k-1;  //定位到最后一个j
        // 定位o
        // 如果不遍历到cnto，那么这种方法会导致j到cnto
        for(int j=po;j<=cnto;++j){
            if(j==cnto){
                flag=false;
                break;
            }
            // o不够了
            if(cnto-j<k){ 
                flag=false; 
                break;
            }
            if(O[j]>J[nj]){
                po=j;       // 记录当前o的位置
                no=j+k-1;   // 定位到最后一个o
                break;
            }
        } 
        for(int m = pi;m<=cnti;++m){

            if(m==cnti){
                flag=false;
                break;
            }
            if(cnti-m<k){ 
                flag=false; 
                break;
            }
            if(I[m]>O[no]){
                pi=m;
                ni=m+k-1;
                break;
            }
        }
        // 如果不可能了，就退出
        if(!flag){
            break;
        }

        // 否则更新答案
        if(((I[ni]-J[i]+1)-3*k)<ans){
            ans=((I[ni]-J[i]+1)-3*k);
        }
    }
    if(ans==1e9){
        cout<<"-1"<<endl;
    }else{
        cout<<ans<<endl;
    }
}
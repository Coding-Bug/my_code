#include<iostream>
using namespace std;
#define maxans 105
#define maxn 20
typedef struct 
{
    int x;
    int y;
}Ans;

Ans ans[maxans];
bool ansvis[maxn][maxn];
char str[maxn][maxn];
int t=0;
int n=0;
int num=0;
void init(){
    num=0;
    for(int i = 0;i<maxn;++i){
        for(int j = 0;j<maxn;++j)
           ansvis[i][j]=false;
    }
}

void dfs(int i,int j,int k){
    //cout<<i<<" "<<j<<endl;
    if(i==n-1&&j==n-1){
       for(int i = 1;i<k;++i){
           ansvis[ans[i].x][ans[i].y]=true;
       }
       num++;
       return;
    }

    if(j+1<n&&str[i][j+1]!='#'&&ansvis[i][j+1]==false){
        ans[k].x=i;
        ans[k].y=j;
        dfs(i,j+1,k+1);
        if(ansvis[i][j]){
            return;
        }
    }
    if(i+1<n&&str[i+1][j]!='#'&&ansvis[i+1][j]==false){
        ans[k].x=i;
        ans[k].y=j;
        dfs(i+1,j,k+1);
        if(ansvis[i][j]){
            return;
        }
    }

    // 向下
    

}
int main(){
   // freopen("test/A.in","r",stdin);
    cin>>t;
    while(t--){
        //cout<<"********** "<<endl;
        init();
        cin>>n;
        for(int i = 0;i<n;++i){
            cin>>str[i];
        }
        

        if(str[0][0]=='#'||str[n-1][n-1]=='#'){
            cout<<0<<endl;
            continue;
        }
        dfs(0,0,0);
        cout<<num<<endl;
    }
    
}
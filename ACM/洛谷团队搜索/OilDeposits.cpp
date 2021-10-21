#include<iostream>
using namespace std;
#define MAX 104
int Move[8][2]={{0,1},{0,-1},{-1,0},{1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
int m,n;
bool str[MAX][MAX];
char c;
int ans=0;

void dfs(int x,int y){
    for(int e= 0 ;e<8;++e){
        int nx=x+Move[e][0];
        int ny=y+Move[e][1];
        if(nx>=0&&nx<m&&ny>=0&&ny<n&&str[nx][ny]){
           str[nx][ny]=false;
           dfs(nx,ny);
        }
    } 
}
int main(){
    //freopen("test/A.txt","r",stdin);
    cin>>m>>n;
    c=getchar();
    while(m!=0){
        ans=0;
        // 输入油田
        for(int i = 0;i<m;++i){
            for(int j = 0;j<n;++j){
               c=getchar();
               if(c=='@'){
                  str[i][j]=true;
               }else{
                  str[i][j]=false;
               }
            }
            getchar();  // 吸收回车
        }
        
        for(int i = 0;i<m;++i){
            for(int j = 0;j<n;++j){
            if(str[i][j]){
                dfs(i,j);
                ans++;
            }
        }
        }
        cout<<ans<<endl;
        cin>>m>>n;
        c=getchar();
    }
}
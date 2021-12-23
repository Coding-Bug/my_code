#include<iostream>
#include<vector>
using namespace std;
int n;
int p,q;
int moves[8][2]={{-1,-2},{1,-2},{-2,-1},{2,-1},{-2,1},{2,1},{-1,2},{1,2},};
vector<pair<int,int> > V;  // 存放路径
bool flag=false;    // 是否已经找到答案
bool vis[27][27];   
void dfs(int x,int y,int cnt){
    if(cnt==p*q){
        flag=true;
        return;
    }
    for(int e=0;e<8;++e){
        if(flag){
            return;
        }
        int nx=x+moves[e][0];
        int ny=y+moves[e][1];
        if(nx<1||nx>p||ny<1||ny>q){
            continue;
        }
        if(!vis[nx][ny]){
            vis[nx][ny]=true;
            pair<int,int> p(nx,ny);
            V.push_back(p);
            dfs(nx,ny,cnt+1);
            if(flag){
                return;
            }
            V.pop_back();
            vis[nx][ny]=false;
        }
    }  
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    int t=0;
    while(n--){
        t++;
        cin>>p>>q;
        cout<<"Scenario #"<<t<<":"<<endl;
        flag=false;
        V.clear();
        for(int i = 0;i<27;++i){
            for(int j=0;j<27;++j){
                vis[i][j]=false;
            }
        }
        for(int i = 1;i<=p;++i){
            for(int j =1;j<=q;++j){
                if(!flag){
                    pair<int,int> p(i,j);
                    V.push_back(p);
                    vis[i][j]=true;
                    dfs(i,j,1);
                    if(!flag){
                       V.pop_back();
                       vis[i][j]=false;
                    }
                }else{
                    break;
                }
            }
        }

        if(!flag){
            cout<<"impossible"<<endl;
        }else{
            int j=V.size();
            for(int i=0;i<j;++i){
                pair<int,int > a=V[i];
                char c=a.second+'A'-1;
                cout<<c<<a.first;
            }
            cout<<endl;
        }
        cout<<endl;
    }
}
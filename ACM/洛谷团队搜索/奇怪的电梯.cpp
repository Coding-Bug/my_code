#include<iostream>
#include<queue>
using namespace std;

int Move[1][2]={-1,1};   // 按钮
int K[203];
bool vis[203];
int step[203];
long long ans=0;
int N,A,B;
void bfs(){
    queue<int> Q;
    Q.push(A);
    vis[A]=true;
    while(!Q.empty()){
        int x;
        x=Q.front();
        Q.pop();
        for(int e = 0;e<2;++e){
            int nx=x+Move[0][e]*K[x];
            if(!vis[nx]&&nx>0&&nx<=N){
                if(nx==B){
                    cout<<step[x]+1<<endl;
                    return;
                }
                step[nx]=step[x]+1;
                vis[nx]=true;
                Q.push(nx);
            }
        }

    }
    cout<<-1<<endl;
    
}
int main(){
    //freopen("test/A.txt","r",stdin);
    cin>>N>>A>>B;
    if(A==B){
        cout<<0<<endl;
        return 0;
    }
    for(int i = 1;i<=N;++i){
        cin>>K[i];
    }
    for(int i = 0;i<203;++i){
        vis[i]=false;
        step[i]=0;
    }
    bfs();
}
#include<iostream>
#include<queue>
using namespace std;
#define MAX 404
typedef struct Node{
    int nx;
    int ny;
    long long step=0;
}Node;
long long step[MAX][MAX];
int n,m;
int x,y;
int Move[8][2]={{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1}};
void bfs(){
     queue<Node> Q;
     // 第一个结点入队
     Node p;
     Node r;
     p.nx=x;
     p.ny=y;
     Q.push(p);
     while(!Q.empty()){
         p=Q.front();
         p.step++;
         Q.pop();
         for(int e=0;e<8;++e){
             int zx=p.nx+Move[e][0];
             int zy=p.ny+Move[e][1];
             if(zx<n&&zx>=0&&zy<m&&zy>=0){
                if(step[zx][zy]==-1||p.step<step[zx][zy]){
                    step[zx][zy]=p.step;
                    r.nx=zx;
                    r.ny=zy;
                    r.step=p.step;
                    Q.push(r);
                }
                
             }
         }
     }
    
}
int main(){
    //freopen("test/A.txt","r",stdin);
    for(int i = 0;i<MAX;++i){
        for(int j = 0;j<MAX;++j){
            step[i][j]=-1;
        }
    }
    cin>>n>>m>>x>>y;
    x--;
    y--;
    step[x][y]=0;
    bfs();
    for(int i = 0;i<n;++i){
        for(int j = 0;j<m;++j){
                printf("%-5d",step[i][j]);
        }
        cout<<endl;
    }
    
}
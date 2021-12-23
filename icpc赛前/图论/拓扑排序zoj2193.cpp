#include<iostream>
#include<queue>
using namespace std;
#define maxn 10
#define maxe 110
string str;
int to[maxe],nex[maxe],head[maxe],in[maxn];
int cnt;
void init(){
    for(int i=0;i<maxe;++i){
        head[i]=-1;
    }
    for(int i = 0;i<maxn;++i){
        in[i]=0;
    }
    cnt=0;
}
void add_edge(int u,int v){
    to[cnt]=v;
    nex[cnt]=head[u];
    head[u]=cnt++;
    in[v]++;
}
bool topology(){
    queue<int> Q;
    // 这里一共九个结点，按照实际情况改
    for(int i=1;i<=9;++i){
        if(in[i]==0){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int p=Q.front();
        Q.pop();
        for(int i=head[p];i!=-1;i=nex[i]){
            in[to[i]]--;
            if(in[to[i]]==0){
                Q.push(to[i]);
            }
        }
    }
    for(int i=1;i<=9;++i){
        if(in[i]!=0){
            return false;
        }
    }
    return true;
}



int main(){
    //freopen("test/A.in","r",stdin);
    while(str!="ENDOFINPUT"){
        init();
        cin>>str;
        if(str=="ENDOFINPUT"){
            break;
        } 
        int a[5][5];
        for(int i =1;i<=4;++i){
            for(int j =1;j<=4;++j){
                cin>>a[i][j];
            }
        }
        cin>>str;

        // 对各自得领域进行分析
        int now=1;
        int mov[4][2]={{1,0},{1,1},{0,1},{0,0}};
        for(int i = 1;i<=3;++i){
            for(int j =1;j<=3;++j){
                for(int e=0;e<4;++e){
                    int nx=i+mov[e][0];
                    int ny=j+mov[e][1];
                    if(a[nx][ny]!=now){
                       
                        add_edge(now,a[nx][ny]);
                    }
                }
                now++;
            }
        }
        if(topology()){
            cout<<"THESE WINDOWS ARE CLEAN"<<endl;
        }else{
            cout<<"THESE WINDOWS ARE BROKEN"<<endl;
        }

    }

}
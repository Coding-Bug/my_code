#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
#define MAX   1003
typedef struct Center
{
    long long x;
    long long y;
    long long z;
    bool isvisit=false;
}Center;

Center P[MAX];
int T;
long long n,h,r;
bool ans=false;

// 判断两个点知否相切或者相交
bool judge(Center a,Center b){
    double ans;
    ans = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
    if(ans<=2*r){
        return true;
    }else{
        return false;
    }
}

int head[MAX];
int headnum=0;
// 广搜
void bfs(){
    queue<int> Q;
    // 全部头节点入队
    for(int i = 0;i<n;++i){
        if(P[i].z-r<=0){
            // if(headnum==0){
            //     head[headnum++]=i;
            // }
            if(h-r<=P[i].z){
                ans=true;
                return ;
            }
            P[i].isvisit=true;
            // 判断它是否和前面的头节点相连
            // for(int j = 0;j<headnum;j++){
            //     if(judge(P[head[j]],P[i])){ // 如果相连，则变为未使用。
            //       P[i].isvisit=false;
            //       break;
            //     }
            // }

            // // 如果没相连，头节点集加一
            // if(!P[i].isvisit){
            //     head[headnum++]=i;
            // }
            Q.push(i);
        }
    }

    while (!Q.empty())
    {
        int x=Q.front();
        Q.pop();
        for(int i = 0;i<n;++i){
            if(!P[i].isvisit){
                if(judge(P[i],P[x])){
                    if(h-r<=P[i].z){
                        ans=true;
                        return;
                    }
                    P[i].isvisit=true;
                    Q.push(i);
                }
            }
        }
    }
    
}


int main(){
    //freopen("test/A.txt","r",stdin);
    cin>>T;
    while(T--){
        ans=false;
        cin>>n>>h>>r;
        // 输入各个求心坐标
        for(int i = 0;i<n;++i){
            cin>>P[i].x>>P[i].y>>P[i].z;
            
            P[i].isvisit=false;
        }
        bfs();
        if(!ans){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }




    }
}
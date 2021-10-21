#include<iostream>
#include<cmath>
using namespace std;
#define maxn 1004
typedef struct Node
{
    double x;
    double y;
}Node;
Node node[maxn];
int f[maxn];
double cal( int i,int j){
    double x1=node[i].x;
    double y1=node[i].y;
    double x2=node[j].x;
    double y2=node[j].y;
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


int find(int x){
    if(f[x]==x){
       return x;
    }
   f[x]=find(f[x]);
   return f[x];
}

void Union(int x,int y){
    if(f[x]==f[y]){
        return;
    }
    f[find(x)]=find(y);
}
// 二分部落之间的最大距离
double l=0;
double r=1e9;
int n,k;

int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>k;
    for(int i =1;i<=n;++i){
        cin>>node[i].x>>node[i].y;
    }
    double mid;   // 两个部落的最小距离
    while(abs(l-r)>1e-5){
        //初始化
        for(int i = 0;i<=n;++i){
            f[i]=i;
        }
        mid= (l+r)/2;
        int cnt=0;   // 不同部落的数量
        for(int i =1;i<=n;++i){
            for(int j = 1;j<=n;++j){
                if(f[i]!=f[j]){
                    if(cal(i,j)<=mid){   //两个点符合在一个部落的距离
                        Union(i,j);
                    }
                }
            }
        }

        for(int i =1;i<=n;++i){
            find(i);
        }
        for(int i = 1;i<=n;++i){
            if(f[i]==i){
                cnt++;
            }
        }
        if(cnt<k){      // 分的部落太少了，那么就说明要求的距离太大了
           r=mid;
        }else{
           l=mid;
        }
    }
    printf("%.2f\n",mid);
    return 0;
}
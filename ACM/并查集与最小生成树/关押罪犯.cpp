#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 40004
#define maxm 100004
inline int read()
{
	char ch;
	int fu=1,x=0;
	for (ch=getchar(); ch<=32; ch=getchar());
	if (ch=='-') fu=-1,ch=getchar();
	for (x=0; ch>32; ch=getchar()) x=x*10+ch-48;
	return x*fu;
}
// 用两倍数组的方式
// 从大到小来分配，每次都将两个人看作敌人
// 敌人的敌人就是朋友，所以，如果枚举到了两个个人，他们本来就是朋友，那没办法，为了使最大值更小，这两个人只能
// 在同一个监狱，此时这个值就是最大了，因为是从大到小枚举的，就不会再大啦
int f[maxn];
int n,m;
typedef struct Edge{
    int u;
    int v;
    int w;
}Edge;

Edge edge[maxm];


bool cmp(Edge a,Edge b){
    return a.w>b.w;
}
int find(int x){
    if(f[x]==x){
        return x;
    }
    f[x]=find(f[x]);
    return f[x];
}

void Union (int x,int y){
    if(f[x]==f[y]){
        return;
    }
    f[find(x)]=find(y);
}
int main(){
    //freopen("test/A.in","r",stdin);
    for(int i=1;i<maxn;++i){
        f[i]=i;
    }
    n=read();
    m=read();
    for(int i = 0;i<m;++i){
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
    }

    sort(edge,edge+m,cmp);    // 权值从大到小排队

    for(int i =0;i<m;++i){
        int u,v;
        u=edge[i].u;
        v=edge[i].v;
        // 在判断的时候，就应该find
        // 保证上一次的被及时更新
        if(find(u)==find(v)){   // 如果他们是朋友，则冲突了，只能是这个最大了
            cout<<edge[i].w<<endl;
            return 0;
        }else{
            Union(u,v+n);
            Union(u+n,v);
            // 不是在这里find全部，会爆时间
            // 如果在这里find(u),find(v)，会太晚了
        }
    }
    // for(int i = 1;i<=n;++i){
    //     cout<<i<<" "<<f[i]<<endl;
    // }

    // 都没有冲突，就输出0
    cout<<0<<endl;


    
}
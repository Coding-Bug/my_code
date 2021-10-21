#include<iostream>
using namespace std;
#define maxn 5004
int n,m,p;
int f[maxn];

int find(int x){
    if(f[x]==x){   // 没有父亲
        return x;
    }
    f[x]= find(f[x]);  // 找根
    return f[x];
}

void Union(int x,int y){
     if(f[x]==f[y]){   // 如果本来就是亲戚关系，则直接返回
         return;
     }

     f[find(x)]=find(y);  // 将x的根连接到一起
}
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n>>m>>p;
    for(int i = 1;i<=n;++i){
        f[i]=i;   // 刚开始每个结点的根都是自己
    }

    for(int i = 0;i<m;++i){
        int x,y;
        cin>>x>>y;
        Union(x,y);  // 将这两个人的亲戚关系结合
    }

    for(int i = 1;i<=n;++i){
        find(i);      // 要再找一遍，不然有的父亲连起来了但是孩子没有更新
    }

    for(int i = 0;i<p;++i){
        int x,y;
        cin>>x>>y;
        if(f[x]==f[y]){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }

    }
}
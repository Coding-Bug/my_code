#include<bits/stdc++.h>
using namespace std;

int n=0;   // 及其部件数
int m=0;   // 供应商数
int w[102][102];    // 供应商的构件重量
int c[102][102];    // 构件的价格
int d=0;   // 价格上限
int minw=0x7fffffff;  // 获得的最小重量
int x[102];  // 临时解向量
int ans[102];// 最终解向量

// i是到了哪个不见，now是现在的重量
void Find(int i,int nW,int nC){
    if(i==n){    // 达到递归出口
        if(nW<minw){
            minw= nW;
            for(int k = 0;k<n;++k){
                ans[k]=x[k];
            }
        }
        return;
    }
    for(int j = 0;j<m;++j){
        if(nC+c[i][j]>d){   // 只进行约束剪
            continue;
        }
        x[i]=j;
        Find(i+1,nW+w[i][j],nC+c[i][j]);  // 递归
    }
}
int main(){
    
    //freopen("test/Robot.txt","r",stdin);
    cin>>n>>m>>d;
    for(int i = 0;i<n;++i){
        for(int j = 0;j<m;++j){
            cin>>w[i][j];
        }
    }
    for(int i = 0;i<n;++i){
        for(int j = 0;j<m;++j){
            cin>>c[i][j];
        }
    }

    Find(0,0,0);
    int i = 0;
    for( i = 0;i<n-1;++i){
        cout<<ans[i]+1<<" " ;
    }
    cout<<ans[i]+1<<endl;
    cout<<minw<<endl;

}
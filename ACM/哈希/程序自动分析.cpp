#include<iostream>
#include<algorithm>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0);
#define maxn 1000007
#define ll long long

typedef struct{
    ll i;
    ll j;
    int e;
}Node;
ll f[maxn];
ll book[3*maxn];   // 离散化的数组
Node node[maxn];
// 将e=1放到前面去
bool cmp(Node a,Node b){
    return a.e>b.e;
}

int find(int x){
    if(x==f[x]){
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


int n,t;

int main(){
    TLE;
    //freopen("test/B.in","r",stdin);
    cin>>t;
    int k=1;
    while(t--){
       int tot=-1;    // book的下标
       cin>>n;
       for(int i =0;i<3*maxn;++i){
           book[i]=0;
       }
       // 输入
       for(int i =1;i<=n;++i){
           cin>>node[i].i>>node[i].j>>node[i].e;
           book[++tot]=node[i].i;
           book[++tot]=node[i].j;
       }

       // 对book进行排序
       sort(book,book+tot);
       // 去重
       int reu=unique(book,book+tot)-book;  
       for(int i = 1;i<=n;++i){
           node[i].i=lower_bound(book,book+reu,node[i].i)-book;
           node[i].j=lower_bound(book,book+reu,node[i].j)-book;
       }
       

       // 初始化f
       for(int i = 0;i<=reu;++i){
           f[i]=i;
       }  
       
       // 
       sort(node+1,node+1+n,cmp);
    //    if(t==0){
    //        for(int i =1;i<=n;++i){
    //            cout<<node[i].i<<" "<<node[i].j<<" "<<node[i].e<<endl;
    //        }
    //    }
       int i = 1;
       for(;i<=n;++i){
           if(node[i].e==1){   // 因为排序了，所以是相等的话，直接合起来
              Union(node[i].i,node[i].j);
           }else{      // 如果不相等，则要判断之前是否相等
              if(find(node[i].i)==find(node[i].j)){
                  cout<<"NO"<<endl;
                  break;
              }
           }
       }
       if(i==n+1){
           cout<<"YES"<<endl;
       }
       

    }
    
}
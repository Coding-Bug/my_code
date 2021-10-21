#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0);
#define maxn 1000007
#define ll long long
unordered_map<string,string> mp;
typedef struct{
    string i;
    string j;
    int e;
}Node;
Node node[maxn];
bool cmp(Node a, Node b){
    return a.e>b.e;
}

string find(string x){
      if(mp[x]==x){
          return x;
      }
      mp[x]=find(mp[x]);
      return mp[x];
}

void Union(string x,string y){
     if(mp[x]==mp[y]){
         return;
     }
     mp[find(x)]=find(y);
}
int t,n;
int main(){
    TLE;
    //freopen("test/C.in","r",stdin);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i = 0;i<n;++i){
            cin>>node[i].i>>node[i].j>>node[i].e;
        }

        sort(node,node+n,cmp);
        
        for(int i = 0;i<n;++i){
           mp[node[i].i]=node[i].i;
           mp[node[i].j]=node[i].j;
        }

        int i=0;
        for(;i<n;++i){
            string a=node[i].i;
            string b=node[i].j;
            if(node[i].e==1){
                Union(a,b);
            }else{
                if(find(a)==find(b)){
                    cout<<"NO"<<endl;
                    break;
                }
            }
        }

        if(i==n){
            cout<<"YES"<<endl;
        }

        
    }
}
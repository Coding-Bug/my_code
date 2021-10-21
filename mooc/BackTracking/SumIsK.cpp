#include<bits/stdc++.h>
using namespace std;
int A[22];    // 数组
long long N,K;
bool flag=false; // 是否找到了最优解    


void Search(int i,long long ans){
    if(ans==K){
            flag=true;
            return;
    }
    if(i==N-1){
        return;
    }
    for(int k=i+1;k<N;++k){
        if(ans+A[k]>K){    // 剪了
            continue;
        }
        Search(k,ans+A[k]);
        if(flag){
            return;
        }
    }
}
int main(){
    //freopen("SumIsK.txt","r",stdin);
    cin>>N>>K;
    for(int i = 0;i<N;++i){
        cin>>A[i];
    }

    Search(0,0);
    if(flag){
     cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
}
#include<bits\stdc++.h>
using namespace std;
int main(){
    freopen("B.txt","w",stdout);
    int N,V;
    cout<<"1"<<endl;
    srand((int)time(NULL));   // 设种子
    N = rand()%20+1;   // 0-1000之间的随机数
    V=rand()%70+1;
    cout<<N<<" "<<V<<endl;
    for(int i = 0;i<N;++i){
        cout<<rand()%80+0<<" ";
    }
    cout<<endl;
    for(int i = 0;i<N;++i){
        cout<<rand()%80+0<<" ";
    }
    cout<<endl;

}
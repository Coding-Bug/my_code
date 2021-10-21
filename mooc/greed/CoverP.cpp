#include<bits/stdc++.h>
using namespace std;
int main(){
    //freopen("test/CoverP.txt","r",stdin);
    int n;    // 点输
    int k;    // 固定长度
    int lP;   // 左端点坐标 
    int ans =1 ;
    cin>>n>>k;
    int*a =new int[n];
    for(int i = 0;i<n;++i){
        cin >>a[i];
    }
    sort(a,a+n);
    lP = a[0];
        for(int i = 0;i<n;++i){
            if((a[i]-lP)>k){
                lP=a[i];
                ans++;
            }
        }

    cout<<ans<<endl;
    delete[] a;
}
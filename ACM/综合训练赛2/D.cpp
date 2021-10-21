#include<iostream>
using namespace std;
const int INF=1e9;
int main(){
    //freopen("test/A.in","r",stdin);
    for(int l=1,r=INF,mid=(l+r)/2,res;l<=r;mid=(l+r)/2){
        cout<<mid<<endl;
        cin>>res;
        cout<<flush;
        if(res==0){
            return 0;
        }else if (res == -1){
            l = mid+1;
        }
         else if (res == 1) {
            r = mid - 1;
        }
    }
}
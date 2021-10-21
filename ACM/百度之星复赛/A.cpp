#include<iostream>
using namespace std;
#define maxn 1000
#define ll long long

int t;
int n,k;

bool judge(){
    if(n==1){
        return false;
    }
    if(k==1){
        return true;
    }

    if(k==2){
        return false;
    }

    if(k==n){
        return true;
    }
    if(k%2==0){
        return false;
    }
    return true;
}
int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(judge()){
            printf("Yes!\n");
        }else{
            printf("No!\n");
        }
         
    }

}
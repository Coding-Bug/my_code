#include<iostream>
using namespace std;

int t=0;
int n=0;
double Max=0;
double Min=0;
double Ave=0;
int main(){
    //freopen("test/A.in","r",stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d%lf%lf%lf",&n,&Max,&Min,&Ave);
        if(n==1){
            if(Ave==Max&&Ave==Min){
                printf("yes\n");
            }else{
                 printf("no\n");
            }
            continue;
        }

        if(n==2){
          if(Max>=Min&&Ave==(Max+Min)/2){
              printf("yes\n");
              
          }else{
              printf("no\n");
          }
          continue;
        }

        if(Max>=Min&&Ave*n<=((n-1)*Max+Min)&&Ave*n>=(Min*(n-1)+Max)){
            
            printf("yes\n");
        }else{
            
            printf("no\n");
        }

    }
    
}
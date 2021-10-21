#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAX 10004
typedef struct Point{
     double x;
     double y;
}Point;
int n;
bool cmp1(Point a,Point b){
     if(a.x==b.x){
         return a.y<b.y;
     }
     return a.x<b.x;
}
bool cmp2(Point a,Point b){
    return a.y<b.y;
}
Point p[MAX];
Point b[MAX];    // 存放中间的数组
int bn=0;       // 

double cal(Point a,Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double  divide(Point A[],int l,int r){
    // 两个点的情况
     if(r-l==1){
         return cal(A[l],A[r]);
     }
     // 三个点的情况
     if(r-l==2){
        double S1=cal(A[l],A[r]);
        double S2=cal(A[l],A[l+1]);
        double S3=cal(A[l+1],A[r]);
        return S1<S2?(S1<S3?S1:S3):(S2<S3?S2:S3);
     }


     int mid=(l+r)/2;
     double S1=divide(A,l,mid);   // 求左边最短
     double S2=divide(A,mid,r);   // 求右边最短
     double S=min(S1,S2);      // 两边的最短距离

     // 将中间符合条件的放到b
     int i,j;
     i=mid;
     j=mid+1;
     bn=0;
     while(i>=l){
         if(A[mid].x-A[i].x<=S){
             b[bn++]=A[i];
         }else{
             break;
         }
         i--;
     }
     while(j<=r){
         if(A[j].x-A[mid].x<=S){
             b[bn++]=A[j];
         }else{
             break;
         }
         j++;
     }

     // 给中间的按y排序
     sort(b,b+bn,cmp2);
     
     for(int i = 0;i<bn-1;++i){
         for(int j = i+1;j<bn;++j){
            if(b[j].y-b[i].y>S){
                break;
            }
                double S3=cal(b[j],b[i]);
                // if(S3==0){
                //     cout<<b[j].x<<","<<b[j].y<<endl;
                //     cout<<b[i].x<<","<<b[i].y<<endl;
                //     exit(1);
                // }
                if(S3<S){
                   S=S3;
                }
         }
     }


     return S;





}
double ans=0;

int main(){
    //freopen("test/A3.txt","r",stdin);
    cin>>n;
    for(int i = 0;i<n;++i){
       cin>>p[i].x>>p[i].y;
    }
    // 让点根据x轴坐标从小到大排队
    sort(p,p+n,cmp1);
    ans=divide(p,0,n-1);
    printf("%.4f\n",ans);
    
}
#include<bits\stdc++.h>
using namespace std;
struct Tower{
    int X;
    int Y;
    int Z;
};

// b是否能盖在a上
bool canCover(Tower a,Tower b){
    if(b.X>a.X&&b.Y>a.Y){
        return true;
    }
    return false;
}
bool cmp(Tower a,Tower b){
    if(a.X>b.X){
        return true;
    }
    if(a.X==b.X&&a.Y>b.Y){
        return true;
    }
    return false;
}
int main(){
    //freopen("test/D.txt","r",stdin);
    int n ; // 塔的个数
    int x,y,z;
    int TN=0;  // 塔的总个数
    int ans=0;
    Tower Tow[190];
    int best[190];
    int Count = 1;
    cin>>n;
    while(n!=0){
        TN=0;
        ans = 0;
    for(int i = 0;i<n;++i){
        cin>>x>>y>>z;
        Tow[TN].X=x;
        Tow[TN].Y=y;
        Tow[TN].Z=z;
        TN++;
        Tow[TN].X=z;
        Tow[TN].Y=y;
        Tow[TN].Z=x;
        TN++;
        Tow[TN].X=x;
        Tow[TN].Y=z;
        Tow[TN].Z=y;
        TN++;
        Tow[TN].X=y;
        Tow[TN].Y=x;
        Tow[TN].Z=z;
        TN++;
        Tow[TN].X=y;
        Tow[TN].Y=z;
        Tow[TN].Z=x;
        TN++;
        Tow[TN].X=z;
        Tow[TN].Y=x;
        Tow[TN].Z=y;
        TN++;
    }
   
    sort(Tow,Tow+TN,cmp);
    for(int i = 0;i<TN;++i){
        best[i]=Tow[i].Z;
    }


    for(int i = 0;i<TN;++i){
        for(int j = 0;j<i;j++){
           if(canCover(Tow[i],Tow[j])){  
               best[i]=max(best[i],best[j]+Tow[i].Z);
           }
        }
        if(best[i]>ans){
            ans = best[i];
        }
    }
    if(ans<0){
        ans = 0;
    }
    printf("Case %d: maximum height = %d\n",Count,ans);
    Count++;
    cin>>n;
    }
}
#include<iostream>
#include<algorithm>
using namespace std;


int main(){
    int pos =0;
    int k;
    char b[260];
    int a[260];
    int num=0;
    bool canvis[260];
    for(int i=0;i<260;++i){
        canvis[i]=true;
        b[i]='\0';
        a[i]=0;
    }
    //freopen("test/A.in","r",stdin);
    scanf("%s%d",&b,&k);
    for(int i=0;b[i]!='\0';++i){
        a[i]=(int)(b[i]-'0');
        if(a[i]==0){
            num++;
        }
        pos=i+1;
    }

    bool flag=true;  // 现在是否递减
    int p1;
    int p2;   // 前面的数
    for(int i = 0;i<k;++i){  // 要删掉的次数
        p1=0;
        //找到第一个还在的数
        while(!canvis[p1]){
            p1++;
        }
        p2=p1+1;
        while(!canvis[p2]){   // 找到p1下一个还没被删的位置
            p2++;
        }
        // 前面小就不删
        while(a[p1]<=a[p2]&&p2<pos){
            p1=p2;
            p2=p1+1;
            while(!canvis[p2]&&p2<pos){   // 找到p1下一个还没被删的位置
                p2++;
            }   
        }
        canvis[p1]=false;   // p1是山峰，删掉
    }

    
    p1=0;
    while(a[p1]==0||!canvis[p1]){  // 去前缀找第一个
       p1++;
       if(p1==pos){
           cout<<"0"<<endl;
           return 0;
        
    }
    }
    

    for(;p1<pos;++p1){
        if(canvis[p1]){
            cout<<a[p1];
        }
    }
    
}
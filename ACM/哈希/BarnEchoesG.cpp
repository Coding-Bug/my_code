#include<iostream>
using namespace std;
#include<cstring>
#define maxn 100
char strA [maxn];
char strB [maxn];
long long mod=1000000003;
long long b[maxn]={1,13};
long long hsA[maxn];   //A串的全部Hash
long long hsB[maxn];   //B串的全部hash

// 求整个串的hs
void make_hashA(int l){   
     hsA[0]=0;
     for(int i = 0,c;i<l;++i){
         c=strA[i]-'a'+1;
         hsA[i+1]=(hsA[i]*b[1]+c)%mod;
     }
}
void make_hashB(int l){
     hsB[0]=0;
     for(int i = 0,c;i<l;++i){
         c=strB[i]-'a'+1;
         hsB[i+1]=(hsB[i]*b[1]+c)%mod;
     }
}

// 快速幂
long long cal (long long base,long long p){
          long long ans=1;
          while(p>0){
             if(p%2!=0){
                ans=(ans*base)%mod;
             }
             base=(base*base)%mod;
             p=p/2;
          }
          return ans;
}


int main(){
    //freopen("test/A.in","r",stdin);
    cin>>strA>>strB;
    int lA=strlen(strA);
    int lB=strlen(strB);
    make_hashA(lA);
    make_hashB(lB);
    // 算处b的取模100次方
    for(int i =2;i<maxn;++i){
        b[i]=cal(b[1],i);
    }

    int ans=0;
    int len=min(lA,lB);
    int k=0;
    while(k<=len){
 
        //cout<<l<<" "<<r<<endl;
        bool flag=false;  // 是否找到了重复部分
        int mid=k;
        // 比较A的前缀和B的后缀Hash
        long long ans1=0;
        long long ans2=0;
        ans1=hsA[mid];
        ans2=(hsB[lB]-(hsB[lB-mid]*b[mid])%mod+mod)%mod;
        
        if(ans1==ans2){
            flag=true;
        }
        // 比较B的前缀和B的后缀
        ans1=0;
        ans2=0;
        ans1=hsB[mid];
        ans2=(hsA[lA]-(hsA[lA-mid]*b[mid])%mod+mod)%mod;

        if(ans1==ans2){
            flag=true;
        }
        if(flag){
            ans=k;
        }
        k++;
        
    }
    cout<<ans<<endl;
}
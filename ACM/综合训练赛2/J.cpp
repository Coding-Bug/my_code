#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;
#define maxn 1004
const  int MAXL = 500;  
#define ll long long
int n;
typedef struct{
    ll  a;
    ll  b;
}Node;
bool cmp(Node a,Node b){
     if(a.b==b.b){
         return a.a<b.a;
     }
     return a.b<b.b;
}


struct  BigNum        
{        
    ll  num[MAXL]={0};        
    int  len;        
};    
BigNum sum;
BigNum ans;

// 高精度乘
BigNum Mul1(BigNum &a, ll &b)        
{        
    BigNum c;        
    ll  i, len;        
    len = a.len;        
    memset(c.num, 0, sizeof(c.num));        
    //乘以0，直接返回0        
    if(b == 0)         
    {        
        c.len = 1;        
        return  c;        
    }        
    for(i = 0; i < len; i++)        
    {        
        c.num[i] += (a.num[i]*b);        
        if(c.num[i] >= 10)        
        {        
            c.num[i+1] = c.num[i]/10;        
            c.num[i] %= 10;        
        }        
    }        
    while(c.num[len] > 0)        
    {        
        c.num[len+1] = c.num[len]/10;        
        c.num[len++] %= 10;        
    }        
    c.len = len;         
    return  c;        
}  

// 高精度除
void Div1(BigNum &a, ll &b, BigNum &c, int &f)        
{        
    ll  i, len = a.len;        
    memset(c.num, 0, sizeof(c.num));        
    f = 0;        
    for(i = a.len-1; i >= 0; i--)        
    {        
        f = f*10+a.num[i];        
        c.num[i] = f/b;        
        f %= b;        
    }        
    while(len > 1 && c.num[len-1] == 0)  
        len--;        
    c.len = len;        
}

// 高精度比较
int  Comp(BigNum &a, BigNum &b)        
{        
    int  i;        
    if(a.len != b.len) return (a.len > b.len) ? 1 : -1;        
    for(i = a.len-1; i >= 0; i--)        
        if(a.num[i] != b.num[i]) return  (a.num[i] > b.num[i]) ? 1 : -1;        
    return  0;        
}



void  Print(BigNum &a)     
{        
    int  i;        
    for(i = a.len-1; i >= 0; i--)        
        printf("%d", a.num[i]);        
    puts("");        
}   
Node node[maxn];
int main(){
    //freopen("test/A.in","r",stdin);
    cin>>n;
    for(int i=0;i<=n;++i){
        cin>>node[i].a>>node[i].b;
    }
    sort(node+1,node+n+1,cmp);
    // for(int i =0;i<=n;++i){
    //    cout<<node[i].a<<" "<<node[i].b<<endl;
    // }
    sum.len=1;
    sum.num[0]=1;
    ans.len=1;
    ans.num[0]=0;
    sum=Mul1(sum,node[0].a);
    for(int i=1;i<=n;++i){
        //cout<<sum<<" "<<node[i].b<<endl;
        BigNum temp;
        int k;
        Div1(sum, node[i].b, temp, k); // 除 
        
        sum=Mul1(sum,node[i].a);
        
        if( Comp(temp, ans)==1){
            ans=temp;
        }
    }
    Print(ans);
}
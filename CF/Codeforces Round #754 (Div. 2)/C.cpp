#include <iostream>
#include <cstring>
using namespace std;
#define maxn 1000010
int t, n;
int a[maxn], b[maxn], c[maxn]; 
int pos[maxn];   // 记录a的位置
int cnt=0;
char str[maxn];

bool solve(int i, int j)
{
    for(int len=2;len<10;++len){
        for(int i=0;i<cnt;++i){
            for(int j =i+1;j<cnt;++j){
                if(pos[j]-pos[i]+1==len){
                    int cnta,cntb,cntc;
                    cnta=cntb=cntc=0;
                    cnta=a[pos[j]]-a[pos[i]]+1;
                    cntb=b[pos[j]]-b[pos[i]];
                    cntc=c[pos[j]]-c[pos[i]];
                    if(cnta>cntb&&cnta>cntc){
                        printf("%d\n",len);
                        return true; 
                    }
                }else if(pos[j]-pos[i]+1>len){
                    break;

                }
            }
        }
    }
    return false;
}
int main()
{
    //freopen("test/A.in","r",stdin);

    scanf("%d", &t);
    while (t--)
    {
        cnt=0;
        scanf("%d", &n);
        scanf("%s", &str);
        for (int i = 0; i <n; ++i)
        {
            a[i] = b[i] = c[i] = 0;
            pos[i]=0;
        }
        int len = strlen(str);
        if (str[0] == 'a')
        {
            a[0] = 1;
        }
        if (str[0] == 'b')
        {
            b[0] = 1;
        }
        if (str[0] == 'c')
        {
            c[0] = 1;
        }
        for (int i = 1; i < len; ++i)
        {
            if (str[i] == 'a')
            {
                a[i] = a[i - 1] + 1;
            }else{
                a[i]=a[i-1];
            }
            if (str[i] == 'b')
            {
                b[i] = b[i - 1] + 1;
            }else{
                b[i]=b[i-1];
            }
            if (str[i] == 'c')
            {
                c[i] = c[i - 1] + 1;
            }else{
                c[i]=c[i-1];
            }
        }

        for(int i = 0;i<len;++i){
            if(str[i]=='a'){
                pos[cnt++]=i;
            }
        }
        if(solve(0,len-1)){
            ;
        }else{
            printf("-1\n");
        }
    }
}
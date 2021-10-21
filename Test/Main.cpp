#include<bits/stdc++.h>
using namespace std;
typedef struct Bone{
    int val;    // 价值
    int vol;    // 体积
}Bone;
bool cmp(Bone a,Bone b){
    if(a.vol==b.vol){
        return a.val>b.val;
    }
    return a.vol<b.vol;
    
}

Bone BO[1003];
int best[1003][1003];

int T;     // 测试用例数
int N;     // 骨头数
int V;     // 背包体积
int ans;   // 答案

// Step 是放到哪一个了，RestV是剩余背包的容积
// val 是value值
int  Find(int Step,int RestV,int val){
    
    // 没有剩余了，返回
    if(Step==N){
        return val;
    }
    // 如果装不下了
    if(RestV<BO[Step].vol){
        return val;
    }
    

    // 如果这种情况的最优解已经有了，也直接返回
    if(best[Step][RestV]!=-1){
        return best[Step][RestV];
    }

    int ans1,ans2;   // 分别是放的答案和不放这个的答案

    ans1 = Find(Step+1,RestV-BO[Step].vol,val+BO[Step].val);
    ans2 = Find(Step+1,RestV,val);   // 不取这个
    if(ans1>ans2){
        best[Step][RestV]=ans1;
    }else{
        best[Step][RestV]=ans2;
    }
    // cout<<Step<<" " <<RestV<<" "<<best[Step][RestV]<<endl;
    return best[Step][RestV];
}
int my(){
    //freopen("A.txt","r",stdin);
    scanf("%d",&T);
    while(T!=0){
        ans = 0;
        scanf("%d%d",&N,&V);   // 输入骨头数和背包体积
        for(int i = 0; i <N;++i){
            scanf("%d",&BO[i].val);
        }
        for(int i = 0; i <N;++i){
            scanf("%d",&BO[i].vol);
        }
        for(int i = 0;i<=N;++i){
            for(int j = 0;j<=V;++j){
                best[i][j]=-1;
            }
        }
        // 给物品排队
        sort(BO,BO+N,cmp);
        // for(int i = 0;i<N;++i){
        //     cout<<"val"<<BO[i].val<<"   "<<"vol:"<<BO[i].vol<<endl;
        // }
        ans = Find(0,V,0);
        //printf("%d\n",ans);
        return ans;
        T--;

    }
    return ans;

}

int max(int x, int y)
{
    return x > y ? x : y;
}

int Hello()
{
    int dp[1000][1000];
    int t, n, v, i, j;
    int va[1000], vo[1000];
    
    cin >> t;
    while (t--)
    {
        cin >> n >> v;
        for (i = 1; i <= n; i++)
            cin >> va[i];
        for (i = 1; i <= n; i++)
            cin >> vo[i];
        memset(dp, 0, sizeof(dp));
        for (i = 1; i <= n; i++)
        {
            for (j = 0; j <= v; j++)
            {
                if (vo[i] <= j)
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - vo[i]] + va[i]);
                else 
                    dp[i][j] = dp[i - 1][j];
            }
        }
        //cout << dp[n][v] << endl;
        return dp[n][v];
    }
    return dp[n][v];
}
void Make(){
    
    int N,V;
    cout<<"1"<<endl;
    srand((int)time(NULL));   // 设种子
    N = rand()%30+1;   // 0-1000之间的随机数
    V=rand()%30+1;
    cout<<N<<" "<<V<<endl;
    for(int i = 0;i<N;++i){
        cout<<rand()%30+0<<" ";
    }
    cout<<endl;
    for(int i = 0;i<N;++i){
        cout<<rand()%30+0<<" ";
    }
    cout<<endl;
    
}
int main(){
    int a,b;
    a= 0;
    b = 0;
    int C=0;
    while(a==b){
    // 生成文件
    freopen("A.txt","w",stdout);
    Make();
    fclose(stdout);
    //freopen("CON","r",stdin);   //加这一句,"CON"代表控制台
    freopen("A.txt","r",stdin);
    a=my();
    fclose(stdin);
    //freopen("CON","r",stdin);   //加这一句,"CON"代表控制台
    freopen("A.txt","r",stdin);
    b = Hello();
    fclose(stdin);
    //freopen("CON","r",stdin);   //加这一句,"CON"代表控制台
    }

    cout<<a<<" "<<b<<endl;


}
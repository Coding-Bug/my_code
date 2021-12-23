#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define maxn 1010
int t, n;
int head[maxn];
int cnt1 = 0;
int tail[maxn];
int cnt2 = 0;

int main()
{
    //freopen("test/A.in","r",stdin);
    cin >> t;
    while (t--)
    {
        for (int i = 0; i < maxn; ++i)
        {
            head[i] = 0;
            tail[i] = 0;
        }
        cnt1 = cnt2=0;
        cin >> n;
        string str;
        cin >> str;
        int len = str.length();
        int i = 0;
        int j = len - 1;
            while (i < j)
            {
                bool flag = false;
                while (i < j)
                {
                    if (str[i] == '1')
                    {
                        head[cnt1++] = i;
                        flag = true;
                        break;
                    }
                    ++i;
                }

                if (flag)
                {
                    while (i < j)
                    {
                        if (str[j] == '0')
                        {
                            tail[cnt2++] = j;
                            flag = true;
                            j--;
                            break;
                        }
                        --j;
                    }

                    i++;
                }
            }

            if (cnt1 + cnt2 == 1||cnt1 + cnt2 == 0)
            {
                cout<<0<<endl;
                continue;
            }
            cout<<1<<endl;
            cout<<cnt1 + cnt2<<" ";
            for (int i = 0; i < cnt1; ++i)
            {
                cout<<head[i]+1<<" ";
            }
            for (int i = cnt2 - 1; i >= 0; --i)
            {
                cout<<tail[i]+1<<" ";
                
            }

            cout<<endl;
     

       
    }
}
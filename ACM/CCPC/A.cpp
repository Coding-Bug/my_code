#include <iostream>
using namespace std;
#include <map>
#define maxn 100005

map<pair<int, int>, int> Q;
int t;
int n;
char str[maxn];
int claU;
int claD;
int claL;
int claR;
int main()
{
  freopen("test/A.in", "r", stdin);
  scanf("%d", &t);
  while (t--)
  {
    Q.clear();
    long long ans = 0;
    scanf("%d", &n);
    getchar();
    scanf("%s", &str);

    claD = claL = claR = claU = 0;

    for (int i = 0; i < n; ++i)
    {

      if (str[i] == 'U')
      {
        claU++;
      }
      if (str[i] == 'L')
      {
        claL++;
      }
      if (str[i] == 'D')
      {
        claD++;
      }
      if (str[i] == 'R')
      {
        claR++;
      }
      if (claD == claU && claL == claR)
      {
        pair<int, int> q(0, 0);
        ans += Q[q];
      }
      else if (claL == claR)
      {
        pair<int, int> q1(claU - claD, claL - claR);
        ans += Q[q1];
        pair<int, int> q2(claD - claU, claL - claR);
        ans += Q[q2];
        pair<int, int> q3(0, claL - claR);
        ans += Q[q3];
      }
      else if (claU == claD)
      {
        pair<int, int> q1(claU - claD, claL - claR);
        ans += Q[q1];
        pair<int, int> q2(claU - claD, claR - claL);
        ans += Q[q2];
        pair<int, int> q3(claU - claD, 0);
        ans += Q[q3];
      }
      else
      {
        pair<int, int> q1(claU - claD, claL - claR);
        ans += Q[q1];
      }

      pair<int, int> p(claD - claU, claR - claL);
      Q[p]++;
    }
    pair<int, int> q(0, 0);
    cout << Q[q] << endl;
    printf("%lld\n", ans);
  }
}
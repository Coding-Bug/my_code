#include <iostream>
#include <queue>
using namespace std;
#define maxn 203

typedef struct Node
{
  int f;
  char c;
  int posi;
  int posj;
  bool operator<(const Node a) const
  {
    if ((a.c == 'Y' && c == 'Y') || (a.c == 'N' && c == 'N'))
    {
      return c < a.c;
    }
    else
    {
      if (c == 'Y')
      {
        return false;
      }
      else
      {
        return true;
      }
    }
  }
} Node;

Node node[maxn][maxn];
priority_queue<Node> Q;
int T;
int n;
int m;
int k;
int ans;
void judge()
{
  Node p[maxn];
  int cnt = 0;
  while (!Q.empty())
  {

    p[cnt++] = Q.top();
    Q.pop();
  }

  priority_queue<Node> Q1;
  for (int i = 0; i < cnt; ++i)
  {
    if (p[i].posi > 1)
    {
      Q1.push(node[p[i].posi - 1][p[i].posj]);
    }
  }
  int pi, pj;
  Node q = Q1.top();
  pi = q.posi;
  pj = q.posj;

  for (int i = 0; i < cnt; ++i)
  {
    if (p[i].posi != pi || p[i].posj != pj)
    {
      Q.push(p[i]);
    }
    else
    {
      ans += p[i].f;
      if (p[i].posi > 1)
      {
        Q.push(node[pi - 1][pj]);
      }
    }
  }
}

int main()
{
  freopen("test/A.in", "r", stdin);
  scanf("%d", &T);
  while (T--)
  {
    ans = 0;
    while (!Q.empty())
    {
      Q.pop();
    }

    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; ++i)
    {
      for (int j = 1; j <= m; ++j)
      {
        scanf("%d", &node[i][j].f);
        getchar();
        node[i][j].c = getchar();
        node[i][j].posi = i;
        node[i][j].posj = j;
      }
    }

    for (int j = 1; j <= m; ++j)
    {
      Q.push(node[n][j]);
    }

    while (!Q.empty())
    {

      Node p = Q.top();
      Q.pop();
      // 出口
      if ((p.c == 'N' && k <= 1) || k == 0)
      {
        ans += p.f;
        break;
      }

      if (p.c == 'N')
      {
        judge();
        k--;
      }
      else
      {
        ans += p.f;
        if (p.posi > 1)
        {
          Q.push(node[p.posi - 1][p.posj]);
        }
      }
    }
    printf("%d\n", ans);
  }
}
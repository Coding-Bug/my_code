#include <bits/stdc++.h>
using namespace std;
#define TLE ios::sync_with_stdio(0),cin.tie(0)
#define MAX_N 100010
int st[MAX_N][20];
 int Query(int l, int r) {
  int k = log2(r - l+1);
  return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
  TLE;
  int n, m;
  cin>>n>>m;
  for (int i = 1; i <= n; ++i)
    cin>>st[i][0];
  for (int k = 1; (1 << k) <= n; ++k)
    for (int i = 1; i + (1 << k) - 1 <= n; ++i)
      st[i][k] = max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    cin>>l>>r;
    cout<<Query(l,r)<<endl;
  }
  return 0;
}
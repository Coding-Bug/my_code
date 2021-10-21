#include <iostream>
#define ll long long
using namespace std;
///
ll t;
ll a, b, c, d, n;
ll ans;
///
ll g(ll x)
{
  ll sumn = 0;
  while (x)
  {
    sumn += x % 10;
    x /= 10;
  }
  return sumn;
}
///
ll f(ll x)
{
  ll gg = g(x);
  return a * x * x * gg + b * x * x + c * x * gg * gg + d * x * gg;
}
///
ll w(ll x)
{
  ll ans = 1;
  while (x)
  {
    x /= 10;
    ans *= 10;
  }
  return ans / 100 == 0 ? 1 : ans / 100;
}
///
int main()
{
  cin >> t;
  while (t--)
  {
    ans = 9999999999999999;
    cin >> a >> b >> c >> d >> n;
    ll wei = w(n);
    for (ll i = wei; i <= n; i += wei)
    {
      ll l = i - wei + 1, r = i;
      while (l < r)
      {
        ll ml = l + (r - l) / 3, mr = r - (r - l) / 3;
        ll fl = f(ml), fr = f(mr);
        if (fl <= fr)
          r = mr - 1;
        else
          l = ml + 1;
      }
      ans = min(min(f(l), f(r)), ans);
    }
    ll l = n / wei * wei, r = n;
    while (l < r)
    {
      ll ml = l + (r - l) / 3, mr = r - (r - l) / 3;
      ll fl = f(ml), fr = f(mr);
      if (fl <= fr)
        r = mr - 1;
      else
        l = ml + 1;
    }
    ans = min(min(f(l), f(r)), ans);
    cout << min(ans, min(f(1), f(n))) << '\n';
  }
  return 0;
}
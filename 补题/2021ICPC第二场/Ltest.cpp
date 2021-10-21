#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef unsigned long long ull;
const ll inf = 1e18;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const double eps = 1e-8;
const int mod = 998244353;

#define fi first
#define se second
#define re register
#define lowbit (-x&x)
int prime[N], phi[N], k, pos[N];
bool is_prime[N];
void get_phi(int n) {
    memset(is_prime, true, sizeof is_prime);
    phi[1] = 1;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) prime[++k] = i, phi[i] = i - 1;
        for (int j = 1; j <= k && i * prime[j] < n; j++) {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
struct node {
    int l, r;
    bool vis[26];
    ll sum, tag;
}t[N<<2];
int a[N];
void push_up(int u) {
    t[u].sum = (t[u<<1].sum + t[u<<1|1].sum) % mod;
    for (int i = 1; i <= 25; i++) t[u].vis[i] = t[u<<1].vis[i] & t[u<<1|1].vis[i];
}
void push_down(int u) {
    if (t[u].tag != 1) {
        t[u<<1].tag = t[u<<1].tag * t[u].tag % mod;
        t[u<<1|1].tag = t[u<<1|1].tag * t[u].tag % mod;
        t[u<<1].sum = t[u<<1].sum * t[u].tag % mod;
        t[u<<1|1].sum = t[u<<1|1].sum * t[u].tag % mod;
        t[u].tag = 1;
    }
}
void build(int u, int l, int r) {
    t[u].l = l, t[u].r = r;
    t[u].tag = 1;
    if (l == r) {
        t[u].sum = phi[a[l]];
        for (int j = 2; j * j <= a[l]; j++) {
            if (a[l] % j == 0) {
                t[u].vis[pos[j]] = 1;
                while (a[l] % j == 0) a[l] /= j;
            }
        }
        if (a[l] != 1) t[u].vis[pos[a[l]]] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(u<<1, l, mid);
    build(u<<1|1, mid+1, r);
    push_up(u);
}
void modify(int u, int ql, int qr, int val) {
    if (ql <= t[u].l && qr >= t[u].r && t[u].vis[pos[val]]) {
        if (t[u].vis[pos[val]]) {
            t[u].sum = t[u].sum * val % mod;
            t[u].tag = t[u].tag * val % mod;
        }
        return;
    }
    if (t[u].l == t[u].r) {
        t[u].sum = t[u].sum * (val - 1) % mod;
        t[u].tag = t[u].tag * (val - 1) % mod;
        t[u].vis[pos[val]] = 1;
        return;
    }
    push_down(u);
    int mid = (t[u].l + t[u].r) >> 1;
    if (ql <= mid) modify(u<<1, ql, qr, val);
    if (qr > mid) modify(u<<1|1, ql, qr, val);
    push_up(u);
}
ll query(int u, int ql, int qr) {
    if (ql <= t[u].l && qr >= t[u].r) return t[u].sum;
    push_down(u);
    int mid = (t[u].l + t[u].r) >> 1;
    ll ans = 0;
    if (ql <= mid) ans = (ans + query(u<<1, ql, qr)) % mod;
    if (qr > mid) ans = (ans + query(u<<1|1, ql, qr)) % mod;
    return ans;
}
void solve() {
    get_phi(1000);
    for (int i = 1; i <= k; i++) pos[prime[i]] = i;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    vector<ll> ans;
    for (int i = 1; i <= m; i++) {
        int opt, l, r, x; cin >> opt;
        if (opt == 0) {
            cin >> l >> r >> x;
            for (int j = 2; j * j <= x; j++) {
                if (x % j == 0) {
                    while (x % j == 0) modify(1, l, r, j), x /= j;
                }
            }
            if (x != 1) modify(1, l, r, x);
        } else {
            cin >> l >> r;
            ans.push_back(query(1, l, r));
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        if (i != ans.size() - 1) printf("%lld\n", ans[i]);
        else printf("%lld", ans[i]);
    }
}

signed main() {
    freopen("test/A.in","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif

#ifdef ACM_LOCAL
    auto start = clock();
#endif
    int t = 1;
//    cin >> t;
    while (t--)
        solve();
#ifdef ACM_LOCAL
    auto end = clock();
    cerr << "Run Time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
#endif
    return 0;
}

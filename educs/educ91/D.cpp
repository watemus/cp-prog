#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
const int MAXN = 100;
#else
const int MAXN = 2e5 + 10;
#endif

struct segtree {
    ll t[MAXN * 4];
    segtree() {
        memset(t, 0, sizeof t);
    }
    void build(ll v, ll lb, ll rb, vec<ll> &arr) {
        if (rb - lb == 1) {
            t[v] = arr[lb];
        } else {
            ll mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, arr);
            build(v * 2 + 2, mid, rb, arr);
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    ll get(ll v, ll lb, ll rb, ll lq, ll rq) {
        if (lq <= lb && rb <= rq) {
            return t[v];
        }
        ll ans = -INFL;
        ll mid = (lb + rb) / 2;
        if (lq < mid) {
            ans = max(ans, get(v * 2 + 1, lb, mid, lq, rq));
        }
        if (mid < rq) {
            ans = max(ans, get(v * 2 + 2, mid, rb, lq, rq));
        }
        return ans;
    }
};

void run() {
    ll n, m;
    cin >> n >> m;
    ll x, k, y;
    cin >> x >> k >> y;
    vec<ll> a(n + 2), b(m);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = -INFI;
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
    }
    ll ss_len = 0;
    vec<ll> ss {0};
    for (ll i = 1; i <= n; i++) {
        if (ss_len < m && a[i] == b[ss_len]) {
            ss_len++;
            ss.push_back(i);
        }
    }
    ss.push_back(n + 1);
    if (ss_len != m) {
        cout << "-1\n";
        return;
    }
    segtree st;
    st.build(0, 0, n + 2, a);
    ll ans = 0;
    for (ll i = 1; i < ss.size(); i++) {
        ll lb = ss[i - 1];
        ll rb = ss[i];
        ll len = rb - lb - 1;
        ll ans_cur = INFL;
        if (len >= k) {
            ans_cur = min({ans_cur, len / k * x + len % k * y, x + (len - k) * y});
        }
        if (st.get(0, 0, n + 2, lb + 1, rb) < max(a[lb], a[rb])) {
            ans_cur = min(ans_cur, y * len);
        }
        if (ans_cur == INFL) {
            cout << "-1\n";
            return;
        }
        ans += ans_cur;
    }
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}



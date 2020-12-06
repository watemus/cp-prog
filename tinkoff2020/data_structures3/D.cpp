//
// Created by watemus on 01.12.2020.
//

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

// #define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1000000000000000069;
constexpr int INFI = 1000000069;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(69);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

int n, q;

const int N = 1e5 + 10;

vec<int> g[N];

const int LOG_N = 20;

int up[LOG_N][N];

int tin[N], tout[N];

int dfs_timer = 1;

void calc_up(int u, int p) {
//  cerr << u << endl;
  tin[u] = dfs_timer++;
  up[0][u] = p;
  for (int i = 1; i < LOG_N; i++) {
    up[i][u] = up[i - 1][up[i - 1][u]];
  }
  for (auto v : g[u]) {
    if (v != p) {
      calc_up(v, u);
    }
  }
  tout[u] = dfs_timer;
//  cerr << u << endl;
}

inline bool is_anc(int u, int v) {
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int calc_lca(int u, int v) {
  if (is_anc(u, v))
    return u;
  for (int i = LOG_N - 1; i >= 0; i--) {
    if (!is_anc(up[i][u], v)) {
      u = up[i][u];
    }
  }
  return up[0][u];
}

namespace fenw {
  int t[N];
  void modify(int pos, int x) {
    for (int i = pos; i < N; i += (i & -i)) {
      t[i] += x;
    }
  }
  int get(int pos) {
    int ans = 0;
    for (int i = pos; i > 0; i -= (i & -i)) {
      ans += t[i];
    }
    return ans;
  }
}  // namespace fenw

const int MOD = 1e9 + 7;

void run() {
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  calc_up(0, 0);
  while (q--) {
    int k, m, r;
    cin >> k >> m >> r;
    r--;
    vec<int> a(k);
    set<int> usd;
    for (int i = 0; i < k; i++) {
      cin >> a[i];
      a[i]--;
      usd.insert(a[i]);
      fenw::modify(tin[a[i]], 1);
      fenw::modify(tout[a[i]], -1);
//      cerr << tin[a[i]] << ' ' << tout[a[i]] << endl;
    }
//    for (int i = 0; i <= n; i++) {
//      cerr << fenw::get(i) << ' ';
//    }
//    cerr << endl;
    vec<pair<int, int>> h(k);
    for (int i = 0; i < k; i++) {
      h[i].second = a[i];
      int lca = calc_lca(a[i], r);
//      cerr << lca << endl;
      h[i].first = fenw::get(tin[r]) + fenw::get(tin[a[i]]) - 2 * fenw::get(tin[lca]) + usd.count(lca) - 1;
//      cerr << fenw::get(tin[r]) << ' ' << fenw::get(tin[a[i]]) << ' ' << fenw::get(tin[lca]) << ' ' << usd.count(lca) << endl;
    }
    sort(ALL(h));
    vec<vec<int>> dp(k, vec<int>(m + 1));
    dp[0][1] = 1;
    for (int i = 1; i < k; i++) {
      for (int j = 1; j <= m; j++) {
        dp[i][j] = (dp[i - 1][j] * 1ll * (j - h[i].first) + dp[i - 1][j - 1]) % MOD;
      }
    }
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
      ans += dp[k - 1][i];
    }
    ans %= MOD;
    for (int i = 0; i < k; i++) {
      fenw::modify(tin[a[i]], -1);
      fenw::modify(tout[a[i]], 1);
    }
    cout << ans << '\n';
  }
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



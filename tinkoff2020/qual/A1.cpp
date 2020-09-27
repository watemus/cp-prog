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

#define int ll

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

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> g(n), rg(n), gc(n), rgc(n);
  vec<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    edges.emplace_back(u, v);
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  vec<int> top_sort;
  vec<int> usd(n);
  function<void(int)> make_top_sort = [&](int v) {
    usd[v] = 1;
    for (auto u : g[v]) {
      if (!usd[u]) {
        make_top_sort(u);
      }
    }
    top_sort.push_back(v);
  };
  for (int i = 0; i < n; i++) {
    if (!usd[i]) {
      make_top_sort(i);
    }
  }
  reverse(ALL(top_sort));
  vec<int> comp(n, -1), sz(n);
  usd.assign(n, 0);
  function<void(int, int)> make_cond = [&](int v, int col) {
    comp[v] = col;
    sz[comp[v]]++;
    for (auto u : rg[v]) {
      if (comp[u] == -1) {
        make_cond(u, col);
      }
    }
  };
  int cnt_conds = 0;
  for (auto v : top_sort) {
    if (comp[v] == -1) {
      make_cond(v, cnt_conds);
      cnt_conds++;
    }
  }
  for (auto [u, v] : edges) {
    if (comp[u] != comp[v]) {
      gc[comp[u]].push_back(comp[v]);
      rgc[comp[v]].push_back(comp[u]);
    }
  }
  vec<int> dp(cnt_conds, -INFL), rdp(cnt_conds, -INFL);
  dp[comp[0]] = rdp[comp[0]] = 0;
  for (int i = 0; i < cnt_conds; i++) {
    for (auto u : rgc[i]) {
      dp[i] = max(dp[i], dp[u] + sz[i]);
    }
  }
  for (int i = cnt_conds - 1; i >= 0; i--) {
    for (auto u : gc[i]) {
      rdp[i] = max(rdp[i], rdp[u] + sz[i]);
    }
  }
  int ans = sz[comp[0]];
  for (auto [u, v] : edges) {
    int cu = comp[u];
    int cv = comp[v];
    if (cu != cv) {
      ans = max(ans, dp[cv] + rdp[cu] + sz[comp[0]]);
    }
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



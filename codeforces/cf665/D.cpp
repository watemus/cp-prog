//
// Created by watemus on 21.08.2020.
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

#ifdef LOCAL
#else
#endif

const int mod = 1e9 + 7;

void run() {
  int n;
  cin >> n;
  vec<vec<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int m;
  cin >> m;
  vec<int> p(m);
  for (int i = 0; i < m; i++) {
    cin >> p[i];
  }
  while (p.size() < n - 1) {
    p.push_back(1);
  }
  sort(ALL(p));
  while (p.size() > n - 1) {
    int a = p.back();
    p.pop_back();
    p.back() *= a;
    p.back() %= mod;
  }
  vec<int> sz(n);
  vec<int> es;
  function<void(int, int)> dfs = [&](int v, int p) {
    sz[v] = 1;
    for (auto u : g[v]) {
      if (u != p) {
        dfs(u, v);
        es.push_back(sz[u] * (n - sz[u]));
        sz[v] += sz[u];
      }
    }
  };
  dfs(0, 0);
  int ans = 0;
  sort(ALL(es));
  for (int i = 0; i < n - 1; i++) {
    ans += es[i] % mod * p[i] % mod;
    ans %= mod;
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



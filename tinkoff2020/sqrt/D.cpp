//
// Created by watemus on 11.10.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int K = 500;
const int C = 1e5 + 10;

void run() {
  int n, m;
  cin >> n >> m;
  vec<int> c(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  vec<vec<int>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vec<int> heavy(n);
  vec<vec<int>> hc(n);
  for (int i = 0; i < n; i++) {
    if (g[i].size() > K) {
      heavy[i] = 1;
      hc[i].resize(C);
    }
  }
  vec<vec<int>> gh(n);
  for (int v = 0; v < n; v++) {
    for (auto u : g[v]) {
      if (heavy[u]) {
        gh[v].push_back(u);
      }
    }
  }
  int ans = 0;
  for (int v = 0; v < n; v++) {
    for (auto u : g[v]) {
      ans += (c[u] != c[v]);
    }
    if (heavy[v]) {
      for (auto u : g[v]) {
        hc[v][c[u]]++;
      }
    }
  }
  ans /= 2;
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int v, nc;
    cin >> v >> nc;
    v--;
    for (auto u : gh[v]) {
      hc[u][c[v]]--;
      hc[u][nc]++;
    }
    if (heavy[v]) {
      ans += hc[v][c[v]];
      ans -= hc[v][nc];
    } else {
      for (auto u : g[v]) {
        ans -= (c[u] != c[v]);
        ans += (c[u] != nc);
      }
    }
    cout << ans << '\n';
    c[v] = nc;
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



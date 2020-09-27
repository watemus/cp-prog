//
// Created by watemus on 23.08.2020.
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

void run() {
  int n, m;
  cin >> n >> m;
  vec<pair<int, int>> edges(m);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  int ans = 0;
  for (int ii = 0; ii < m; ii++) {
    swap(edges[ii].first, edges[ii].second);
    {
      vec<vec<int>> g(n), rg(n), gc(n), rgc(n);
      for (int i = 0; i < m; i++) {
        int u, v;
        tie(u, v) = edges[i];
        g[u].push_back(v);
        rg[v].push_back(u);
      }
      vec<int> top_sort, usd(n);
      function<void(int)> make_top_sort = [&](int v) {
        usd[v] = 1;
        for (auto u : g[v]) {
          if (!usd[u])
            make_top_sort(u);
        }
        top_sort.push_back(v);
      };
      for (int i = 0; i < n; i++) {
        if (!usd[i])
          make_top_sort(i);
      }
      reverse(ALL(top_sort));
      usd.assign(n, 0);
      vec<int> size(n);
      vec<int> comp(n, -1);
      map<pair<int, int>, int> ecnt, recnt;
      function<void(int, int)> make_cond = [&](int v, int col) {
        usd[v] = 1;
        size[col]++;
        comp[v] = col;
        for (auto u : rg[v]) {
          if (!usd[u]) {
            make_cond(u, col);
          }
        }
      };
      int col = 0;
      for (auto v : top_sort) {
        if (!usd[v]) {
          make_cond(v, col);
          col++;
        }
      }
      for (int u : top_sort) {
        for (int v : g[u]) {
          if (comp[u] != comp[v]) {
            gc[comp[u]].push_back(comp[v]);
            ecnt[{comp[u], comp[v]}]++;
            rgc[comp[v]].push_back(comp[u]);
            recnt[{comp[v], comp[u]}]++;
          }
        }
      }
      ans = max(ans, size[comp[0]]);
    }
    swap(edges[ii].first, edges[ii].second);
  }
  {
    vec<vec<int>> g(n), rg(n), gc(n), rgc(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      tie(u, v) = edges[i];
      g[u].push_back(v);
      rg[v].push_back(u);
    }
    vec<int> top_sort, usd(n);
    function<void(int)> make_top_sort = [&](int v) {
      usd[v] = 1;
      for (auto u : g[v]) {
        if (!usd[u])
          make_top_sort(u);
      }
      top_sort.push_back(v);
    };
    for (int i = 0; i < n; i++) {
      if (!usd[i])
        make_top_sort(i);
    }
    reverse(ALL(top_sort));
    usd.assign(n, 0);
    vec<int> size(n);
    vec<int> comp(n, -1);
    map<pair<int, int>, int> ecnt, recnt;
    function<void(int, int)> make_cond = [&](int v, int col) {
      usd[v] = 1;
      size[col]++;
      comp[v] = col;
      for (auto u : rg[v]) {
        if (!usd[u]) {
          make_cond(u, col);
        }
      }
    };
    int col = 0;
    for (auto v : top_sort) {
      if (!usd[v]) {
        make_cond(v, col);
        col++;
      }
    }
    for (int u : top_sort) {
      for (int v : g[u]) {
        if (comp[u] != comp[v]) {
          gc[comp[u]].push_back(comp[v]);
          ecnt[{comp[u], comp[v]}]++;
          rgc[comp[v]].push_back(comp[u]);
          recnt[{comp[v], comp[u]}]++;
        }
      }
    }
    ans = max(ans, size[comp[0]]);
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



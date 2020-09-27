//
// Created by watemus on 10.08.2020.
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

void dfs(int v, vec<int> &col, vec<vec<int>> &g, int &max_col) {
  max_col = max(max_col, col[v]);
  for (auto u : g[v]) {
    if (col[u] == -1) {
      col[u] = col[v] + 1;
      dfs(u, col, g, max_col);
    }
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int max_col = 0;
  vec<int> col(n, -1);
  col[0] = 0;
  dfs(0, col, g, max_col);
  vec<vec<int>> at_col(max_col + 1);
  for (int i = 0; i < n; i++) {
    at_col[col[i]].push_back(i);
  }
  int nm = (n + 1) / 2;
  if (max_col >= nm - 1) {
    cout << "PATH\n";
    cout << max_col + 1 << '\n';
    int to = at_col[max_col].back();
    for (int cl = max_col; cl >= 0; cl--) {
      cout << to + 1 << ' ';
      for (auto u : g[to]) {
        if (col[u] + 1 == col[to]) {
          to = u;
          break;
        }
      }
    }
    cout << '\n';
  } else {
    cout << "PAIRING\n";
    vec<pair<int, int>> ans;
    for (int i = 0; i <= max_col; i++) {
      for (int j = 0; j + 1 < at_col[i].size(); j += 2) {
        ans.emplace_back(at_col[i][j], at_col[i][j + 1]);
      }
    }
    cout << ans.size() << '\n';
    for (auto [u, v] : ans) {
      cout << u + 1 << ' ' << v + 1 << '\n';
    }
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



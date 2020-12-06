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

const int N = 3e5 + 10;

vec<int> g[N];
map<int, int> mp[N];
int dep[N];
vec<pair<int, int>> queries[N];
int ans[N], sz[N];

void dfs(int u) {
  sz[u] = 1;
  for (auto &v : g[u]) {
    dfs(v);
    sz[u] += sz[v];
    if (sz[v] > sz[g[u][0]]) {
      swap(v, g[u][0]);
    }
  }
  if (!g[u].empty()) {
    mp[u].swap(mp[g[u][0]]);
    dep[u] = dep[g[u][0]] + 1;
    for (int i = 1; i < g[u].size(); i++) {
      int v = g[u][i];
      for (auto [k, val] : mp[v]) {
        mp[u][k + dep[v] + 1 - dep[u]] += val;
      }
    }
  } else {
    dep[u] = 0;
  }
  mp[u][-dep[u]]++;
  for (auto [d, i] : queries[u]) {
    if (mp[u].count(d - dep[u]))
      ans[i] = mp[u][d - dep[u]];
  }
}

void run() {
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int anc;
    cin >> anc;
    g[anc - 1].push_back(i);
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int u, d;
    cin >> u >> d;
    u--;
    queries[u].emplace_back(d, i);
  }
  dfs(0);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
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



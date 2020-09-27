//
// Created by watemus on 08.09.2020.
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

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

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
  vec<array<vec<int>, 2>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[v][c].push_back(u);
  }
  vec<int> ans(n);
  vec<set<int>> cnt(n);
  vec<int> dist(n, -1);
  queue<int> q;
  q.push(n - 1);
  dist[n - 1] = 0;
  while (q.size()) {
    int v = q.front();
    q.pop();
    for (auto u : g[v][0]) {
      if (cnt[u].size() < 2) {
        ans[u] = 1;
        cnt[u].insert(1);
        if (cnt[u].size() == 2 && dist[u] == -1) {
          dist[u] = dist[v] + 1;
          ans[u] = 1 - ans[u];
          q.push(u);
        }
      }
    }
    for (auto u : g[v][1]) {
      if (cnt[u].size() < 2) {
        ans[u] = 0;
        cnt[u].insert(0);
        if (cnt[u].size() == 2 && dist[u] == -1) {
          dist[u] = dist[v] + 1;
          ans[u] = 1 - ans[u];
          q.push(u);
        }
      }
    }
  }
  cout << dist[0] << '\n';
  for (auto el : ans) {
    cout << el;
  }
  cout << '\n';
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



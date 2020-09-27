//
// Created by watemus on 05.08.2020.
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
  int n, S;
  cin >> n >> S;
  vec<vec<tuple<int, int, int>>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, w, c;
    cin >> u >> v >> w >> c;
    u--, v--;
    g[u].emplace_back(v, w, c);
    g[v].emplace_back(u, w, c);
  }
  vec<int> cnt_leaves(n);
  set<tuple<int, int, int>> edges1, edges2;
  int sm = 0;
  function<void(int, int)> dfs = [&](int v, int p) {
    int cnt_ch = 0;
    for (auto [u, w, c] : g[v]) {
      if (u != p) {
        cnt_ch++;
        dfs(u, v);
        if (c == 1) {
          edges1.emplace(-(w * cnt_leaves[u] - (w / 2 * cnt_leaves[u])), w, u);
        } else {
          edges2.emplace(-(w * cnt_leaves[u] - (w / 2 * cnt_leaves[u])), w, u);
        }
        sm += w * cnt_leaves[u];
        cnt_leaves[v] += cnt_leaves[u];
      }
    }
    if (!cnt_ch) {
      cnt_leaves[v] = 1;
    }
  };
  dfs(0, 0);
  vec<int> p1(1), p2(1);
  while (edges1.size()) {
    auto[dt, w, v] = *edges1.begin();
    if (dt == 0) break;
    edges1.erase(edges1.begin());
    int nw = w / 2;
    edges1.emplace(-nw * cnt_leaves[v] + (nw / 2 * cnt_leaves[v]), nw, v);
    p1.push_back(p1.back() - dt);
  }
  while (edges2.size()) {
    auto[dt, w, v] = *edges2.begin();
    if (dt == 0) break;
    edges2.erase(edges2.begin());
    int nw = w / 2;
    edges2.emplace(-nw * cnt_leaves[v] + (nw / 2 * cnt_leaves[v]), nw, v);
    p2.push_back(p2.back() - dt);
  }
  int ans = INFI;
  for (int i = 0; i < p2.size(); i++) {
    int c1 = lower_bound(ALL(p1), sm - S - p2[i]) - p1.begin();
    if (c1 < p1.size())
      ans = min(ans, i * 2 + c1);
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



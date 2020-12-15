//
// Created by watemus on 14.12.2020.
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

const int N = 1010;

namespace flows {
  struct Edge {
    int u;
    int v;
    int cap;
    int flow;
  };
  vec<Edge> edges;
  vec<int> g[N];

  void init() {
    edges.clear();
    fill(g, g + N, vec<int>(0));
  }

  void add_edge(int u, int v, int cap) {
    g[u].push_back(edges.size());
    edges.push_back({u, v, cap, 0});
    g[v].push_back(edges.size());
    edges.push_back({v, u, 0, 0});
  }

  int q[N];
  int level[N];

  bool bfs(int s, int t) {
    memset(level, -1, sizeof level);
    int qf = 0;
    int qs = 1;
    q[qf] = s;
    level[s] = 0;
    while (qf < qs) {
      int u = q[qf++];
      for (auto id : g[u]) {
        auto &e = edges[id];
        if (e.flow < e.cap && level[e.v] == -1) {
          level[e.v] = level[u] + 1;
          q[qs++] = e.v;
        }
      }
    }
    return level[t] != -1;
  }

  int ptr[N];

  int dfs(int u, int flow, int t) {
    if (u == t) {
      return flow;
    }
    if (flow == 0) {
      return 0;
    }
    for (; ptr[u] < g[u].size(); ptr[u]++) {
      int id = g[u][ptr[u]];
      auto &e = edges[g[u][ptr[u]]];
      if (e.flow < e.cap && level[e.v] == level[u] + 1) {
        int pushed = dfs(e.v, min(flow, e.cap - e.flow), t);
        if (pushed) {
          edges[id].flow += pushed;
          edges[id ^ 1].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  int max_flow(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
      int pushed = 0;
      memset(ptr, 0, sizeof ptr);
      do {
        pushed = dfs(s, INFI, t);
        ans += pushed;
      } while (pushed != 0);
    }
    return ans;
  }
}

constexpr ld EPS = 1e-8;

ld dist(pair<ld, ld> a, pair<ld, ld> b) {
  return sqrtl((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<pair<ld, ld>> a(n), b(m);
  vec<int> c(m);
  for (auto &[x, y] : a) {
    cin >> x >> y;
  }
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    b[i] = {x, y};
    cin >> c[i];
  }
  vec<ld> dists;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      dists.push_back(dist(a[i], b[j]));
    }
  }
  sort(ALL(dists));
  int l = -1;
  int r = dists.size() - 1;
  int s = N - 1;
  int t = N - 2;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    flows::init();
    for (int i = 0; i < n; i++) {
      flows::add_edge(s, i, 1);
    }
    for (int i = 0; i < m; i++) {
      flows::add_edge(n + i, t, c[i]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (dist(a[i], b[j]) < dists[mid] + EPS) {
          flows::add_edge(i, j + n, 1);
        }
      }
    }
    int flow = flows::max_flow(s, t);
    if (flow == n) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << fixed << setprecision(20);
  cout << dists[r] << '\n';
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



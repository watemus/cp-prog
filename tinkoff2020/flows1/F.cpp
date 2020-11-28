//
// Created by watemus on 09.11.2020.
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

const int N = 71;

int c[N][N];
char f[N][N];

struct Edge {
  int u;
  int v;
  int flow;
  int cap;
};

vec<Edge> edges;
vec<int> g[N * N];

void add_edge(int u, int v, int cap) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, 0, cap});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0});
}

int q[N * N];
int level[N * N];

bool bfs(int s, int t) {
  memset(level, -1, sizeof level);
  int qf = 0;
  int qs = 1;
  q[qf] = s;
  level[s] = 0;
  while (qf < qs) {
    int u = q[qf++];
    for (int id : g[u]) {
      auto &e = edges[id];
      if (level[e.v] == -1 && e.flow < e.cap) {
        level[e.v] = level[u] + 1;
        q[qs++] = e.v;
      }
    }
  }
  return level[t] != -1;
}

int ptr[N * N];

int dfs(int u, int flow, int t) {
  if (u == t)
    return flow;
  if (flow == 0)
    return 0;
  for (; ptr[u] < g[u].size(); ptr[u]++) {
    int id = g[u][ptr[u]];
    auto &e = edges[id];
    if (level[e.v] != level[u] + 1) {
      continue;
    }
    int pushed = dfs(e.v, min(flow, e.cap - e.flow), t);
    if (pushed) {
      edges[id].flow += pushed;
      edges[id ^ 1].flow -= pushed;
      return pushed;
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
      pushed = dfs(s, INFL, t);
      ans += pushed;
    } while (pushed != 0);
  }
  return ans;
}
void run() {
  for (int i = 0; i < N; i++) {
    memset(f[i], '.', sizeof f[i]);
  }
  int n, m;
  cin >> n >> m;
  int w, b, g;
  cin >> w >> b >> g;
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      c[i][j] = cnt++;
      cin >> f[i][j];
    }
  }
  int s = cnt++;
  int t = cnt++;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (f[i][j] == 'W') {
        add_edge(s, c[i][j], 2 * b);
      } else {
        add_edge(c[i][j], t, 2 * w);
      }
      for (auto [di, dj] : DD) {
        if (i + di >= 1 && i + di <= n && j + dj >= 1 && j + dj <= m) {
          add_edge(c[i][j], c[i + di][j + dj], g);
          add_edge(c[i + di][j + dj], c[i][j], g);
        }
      }
    }
  }
  int ans = max_flow(s, t);
  cout << ans / 2 << '\n';
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



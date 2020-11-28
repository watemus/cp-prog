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

const int N = 510;

struct Edge {
  int u;
  int v;
  int flow;
  int cap;
};

vec<Edge> edges;

vec<int> g[N];

void add_edge(int u, int v, int c) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, 0, c});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0});
}

int q[N];
int level[N];

bool bfs(int s, int t, int min_flow) {
  memset(level, -1, sizeof level);
  level[s] = 0;
  q[0] = s;
  int qs = 0;
  int qf = 1;
  while (qs < qf) {
    int u = q[qs];
    qs++;
    for (int id : g[u]) {
      auto &e = edges[id];
      if (level[e.v] == -1 && e.flow < e.cap && e.cap - e.flow >= min_flow) {
        q[qf++] = e.v;
        level[e.v] = level[u] + 1;
      }
    }
  }
  return level[t] != -1;
}

int ptr[N];

int dfs(int u, int flow, int min_flow, int t) {
  if (u == t)
    return flow;
  if (flow < min_flow)
    return 0;
  for (; ptr[u] < g[u].size(); ptr[u]++) {
    int id = g[u][ptr[u]];
    auto &e = edges[id];
    if (level[e.v] != level[e.u] + 1) continue;
    int pushed = dfs(e.v, min(flow, e.cap - e.flow), min_flow, t);
    if (pushed > 0) {
      edges[id].flow += pushed;
      edges[id ^ 1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}

int max_flow(int s, int t) {
  int ans = 0;
  for (int min_flow = (1LL << 31); min_flow > 0; min_flow >>= 1) {
    while (bfs(s, t, min_flow)) {
      memset(ptr, 0, sizeof ptr);
      int pushed = 0;
      do {
        pushed = dfs(s, INFL, min_flow, t);
        ans += pushed;
      } while (pushed != 0);
    }
  }
  return ans;
}

void run() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    add_edge(u, v, c);
  }
  cout << max_flow(0, n - 1) << '\n';
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



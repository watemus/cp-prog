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

struct Edge {
  int u;
  int v;
  int cap;
  int flow;
};

const int N = 500;

vec<Edge> edges;
vec<int> g[N];

void add_edge(int u, int v, int cap) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, cap, 0});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0});
}

int level[N];
int q[N];

bool bfs(int s, int t) {
  memset(level, -1, sizeof level);
  level[s] = 0;
  int qs = 1;
  int qf = 0;
  q[qf] = s;
  while (qf < qs) {
    int u = q[qf++];
    for (auto id : g[u]) {
      auto &e = edges[id];
      if (level[e.v] == -1 && e.flow < e.cap) {
        level[e.v] = level[e.u] + 1;
        q[qs++] = e.v;
      }
    }
  }
  return level[t] != -1;
}

int ptr[N];

int dfs(int u, int flow, int t) {
  if (flow == 0)
    return 0;
  if (u == t)
    return flow;
  for (; ptr[u] < g[u].size(); ptr[u]++) {
    int id = g[u][ptr[u]];
    auto &e = edges[id];
    if (level[e.v] != level[e.u] + 1) continue;
    int pushed = dfs(e.v, min(flow, e.cap - e.flow), t);
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
  while (bfs(s, t)) {
    int pushed = 0;
    memset(ptr, 0, sizeof ptr);
    do {
      pushed = dfs(s, INFL, t);
      ans += pushed;
    } while (pushed > 0);
  }
  return ans;
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  int s = 2 * n;
  int t = 2 * n + 1;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] > 0) {
      ans += a[i];
      add_edge(s, i, a[i]);
    }
    if (a[i] < 0) {
      add_edge(i + n, t, -a[i]);
    }
  }
  vec<vec<int>> gg(n);
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int v;
      cin >> v;
      v--;
      gg[i].push_back(v);
    }
  }
  vec<int> cr, usd(n);
  function<void(int)> dfsik = [&](int u) {
    usd[u] = 1;
    for (auto v : gg[u]) {
      if (!usd[v]) {
        cr.push_back(v);
        dfsik(v);
      }
    }
  };
  for (int i = 0; i < n; i++) {
    usd.assign(n, 0);
    cr.clear();
    dfsik(i);
    for (auto v : cr) {
      add_edge(i, v + n, INFI);
    }
  }
  cout << ans - max_flow(s, t) << '\n';
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



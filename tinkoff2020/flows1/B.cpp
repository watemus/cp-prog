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

const int N = 505;

int c_in[N][N], c_out[N][N];
int xs[N * N], ys[N * N];
char f[N][N];

int pr[N * N];
int sz[N * N];

int d_get(int v) {
  if (pr[v] == -1) return v;
  return pr[v] = d_get(pr[v]);
}

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

int level[N * N];
int q[N * N];

bool bfs(int s, int t) {
  memset(level, -1, sizeof level);
  level[s] = 0;
  int qf = 1;
  int qs = 0;
  q[qs] = s;
  while (qs < qf) {
    int u = q[qs++];
    for (int id : g[u]) {
      auto &e = edges[id];
      if (e.flow < e.cap && level[e.v] == -1) {
        q[qf++] = e.v;
        level[e.v] = level[u] + 1;
      }
    }
  }
  return level[t] != -1;
}

int ptr[N * N];

int dfs(int u, int flow, int t) {
  if (flow == 0) return 0;
  if (u == t) return flow;
  for (; ptr[u] < g[u].size(); ptr[u]++) {
    int id = g[u][ptr[u]];
    auto &e = edges[id];
    if (level[e.v] != level[u] + 1) continue;
    int pushed = dfs(e.v, min(e.cap - e.flow, flow), t);
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
    } while (pushed != 0);
  }
  return ans;
}

void d_unite(int u, int v) {
  u = d_get(u);
  v = d_get(v);
  if (u == v)
    return;
  if (sz[u] < sz[v])
    swap(u, v);
  pr[v] = u;
  sz[u] += sz[v];
}

int used[N * N];

void find_min_cut(int v) {
  used[v] = 1;
  for (int id : g[v]) {
    auto &e = edges[id];
    if (id & 1) continue;
    if (e.flow < e.cap && !used[e.v])
      find_min_cut(e.v);
  }
}

void run() {
  memset(pr, -1, sizeof pr);
  fill(sz, sz + N * N, 1);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < N; i++) {
    memset(f[i], '#', sizeof f[i]);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      c_in[i][j] = ((i - 1) * m + j - 1) * 2;
      c_out[i][j] = ((i - 1) * m + j - 1) * 2 + 1;
      xs[c_in[i][j]] = i;
      ys[c_in[i][j]] = j;
      f[i][j] = '.';
    }
  }
  int k, l;
  cin >> k >> l;
  for (int i = 0; i < k; i++) {
    int x, y;
    cin >> x >> y;
    f[x][y] = '#';
  }
  for (int i = 0; i < l; i++) {
    int x, y;
    cin >> x >> y;
    f[x][y] = '*';
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (f[i][j] == '.') {
        for (auto [di, dj] : DD) {
          if (f[i + di][j + dj] == '.') {
            d_unite(c_in[i][j], c_in[i + di][j + dj]);
            d_unite(c_out[i][j], c_out[i + di][j + dj]);
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!used[d_get(c_in[i][j])]) {
        if (f[i][j] == '.') {
          add_edge(d_get(c_in[i][j]), d_get(c_out[i][j]), INFI);
        } else if (f[i][j] == '*') {
          add_edge(d_get(c_in[i][j]), d_get(c_out[i][j]), 1);
        }
        used[d_get(c_in[i][j])] = 1;
      }
      for (auto [di, dj] : DD) {
        int good = int(f[i][j] == '*') + int(f[i + di][j + dj] == '*');
        int bad = int(f[i][j] == '#') + int(f[i + di][j + dj] == '#');
        if (good && !bad) {
          add_edge(d_get(c_out[i][j]), d_get(c_in[i + di][j + dj]), INFI);
        }
      }
    }
  }
  int xa, ya;
  cin >> xa >> ya;
  int xb, yb;
  cin >> xb >> yb;
  if (d_get(c_in[xa][ya]) == d_get(c_in[xb][yb])) {
    cout << "-1\n";
    return;
  }
  int ans = max_flow(d_get(c_in[xa][ya]), d_get(c_out[xb][yb]));
  cout << ans << '\n';
  memset(used, 0, sizeof used);
  bfs(d_get(c_in[xa][ya]), d_get(c_out[xb][yb]));
  set<pair<int, int>> ansik;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (level[c_in[i][j]] != -1 && level[c_out[i][j]] == -1 && f[i][j] == '*') {
        ansik.emplace(i, j);
      }
    }
  }
  assert(ans == ansik.size());
  for (auto [x, y] : ansik) {
    cout << x << " " << y << '\n';
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




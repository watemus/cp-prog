//
// Created by watemus on 10.11.2020.
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

struct Edge {
  int u;
  int v;
  int flow;
  int cap;
};

const int N = 3000;

vec<int> g[N];
vec<Edge> edges;

void add_edge(int u, int v, int cap) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, 0, cap});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0});
}

int q[N];
int level[N];

bool bfs(int s, int t) {
  memset(level, -1, sizeof level);
  level[s] = 0;
  int qf = 0;
  int qs = 1;
  q[qf] = s;
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

int ptr[N];

int dfs(int u, int flow, int t) {
  if (u == t)
    return flow;
  if (flow == 0)
    return 0;
  for (; ptr[u] < g[u].size(); ptr[u]++) {
    int id = g[u][ptr[u]];
    auto &e = edges[id];
    if (level[e.v] != level[u] + 1)
      continue;
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
  int n, k;
  cin >> n >> k;
  vec<vec<int>> a(k, vec<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      cin >> a[j][i];
    }
  }
  auto sa = a;
  vec<int> meds(k);
  for (int i = 0; i < k; i++) {
    sort(ALL(sa[i]));
    meds[i] = sa[i][n / 2];
  }
  vec<int> cls(n);
  for (int i = 0; i < n; i++) {
    if (a[0][i] < meds[0])
      cls[i] = 0;
    else
      cls[i] = 1;
  }
  int MX = 1;
  for (int i = 1; i < k; i++) {
    MX *= 3;
  }
  vec<int> to(n);
  vec<vec<int>> ids_in(MX), ids_out(MX);
  for (int i = 1; i < k; i++) {
    for (int j = 0; j < n; j++) {
      int dig;
      if (a[i][j] < meds[i])
        dig = 0;
      else if (a[i][j] == meds[i])
        dig = 1;
      else
        dig = 2;
      to[j] = to[j] * 3 + dig;
    }
  }
  for (int i = 0; i < n; i++) {
    if (cls[i] == 0)
      ids_in[to[i]].push_back(i);
    else
      ids_out[to[i]].push_back(i);
  }
  int s = MX * 2 + 1;
  int t = MX * 2 + 2;
  for (int mask1 = 0; mask1 < MX; mask1++) {
    if (ids_in[mask1].size())
      add_edge(s, mask1, ids_in[mask1].size());
    if (ids_out[mask1].size())
      add_edge(MX + mask1, t, ids_out[mask1].size());
    for (int mask2 = 0; mask2 < MX; mask2++) {
      int cmask1 = mask1, cmask2 = mask2;
      bool ok = true;
      for (int i = 1; i < k; i++) {
        if (abs(cmask1 % 3 - cmask2 % 3) == 0 && cmask1 % 3 != 1) {
          ok = false;
          break;
        }
        cmask1 /= 3;
        cmask2 /= 3;
      }
      if (ok) {
        add_edge(mask1, MX + mask2, INFI);
      }
    }
  }
  int mf = max_flow(s, t);
  if (mf == n / 2) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
    return;
  }
  vec<vec<int>> flow(N, vec<int>(N));
  for (auto &e : edges) {
    flow[e.u][e.v] = e.flow;
  }
  vec<pair<int, int>> ans;
  for (int i = 0; i < MX; i++) {
    for (int j = MX; j < MX * 2; j++) {
      while (flow[i][j] > 0) {
        ans.emplace_back(ids_in[i].back(), ids_out[j - MX].back());
        ids_in[i].pop_back();
        ids_out[j - MX].pop_back();
        flow[i][j]--;
      }
    }
  }
  for (auto [x, y] : ans) {
    cout << x + 1 << ' ' << y + 1 << '\n';
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



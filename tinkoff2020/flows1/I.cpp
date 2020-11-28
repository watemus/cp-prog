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
  int cost;
};

const int N = 110;

vec<int> g[N];
vec<Edge> edges;

void add_edge(int u, int v, int cap, int cost) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, 0, cap, cost});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0, -cost});
}

int dist[N], pot[N];

int q[N * N];
int in_q[N];
void Ford_Bellman(int s, int t) {
  int qf = 0;
  int qs = 1;
  q[qf] = s;
  fill(pot, pot + N, INFL);
  pot[s] = 0;
  memset(in_q, 0, sizeof in_q);
  while (qf < qs) {
    int u = q[qf++];
    for (auto id : g[u]) {
      auto &e = edges[id];
      if (pot[e.v] > pot[e.u] + e.cost && e.flow < e.cap) {
        pot[e.v] = pot[e.u] + e.cost;
        if (!in_q[e.v])
          q[qs++] = e.v;
        in_q[e.v] = 1;
      }
    }
    in_q[u] = 0;
  }
}

int usd[N];
int pr[N];

bool Dijkstra(int s, int t) {
  fill(dist, dist + N, INFL);
  memset(usd, 0, sizeof usd);
  memset(pr, -1, sizeof pr);
  dist[s] = 0;
  set<pair<int, int>> st;
  st.emplace(0, s);
  while (st.size()) {
    auto [d, u] = *st.begin();
    st.erase(st.begin());
    if (d > dist[u]) continue;
    for (auto id : g[u]) {
      auto &e = edges[id];
      int w = pot[e.u] - pot[e.v] + e.cost;
      if (dist[u] + w < dist[e.v] && e.flow < e.cap) {
        dist[e.v] = dist[u] + w;
        pr[e.v] = id;
        st.emplace(dist[e.v], e.v);
      }
    }
  }
  return dist[t] != INFL;
}

int min_cost_max_flow(int s, int t) {
  Ford_Bellman(s, t);
  int ans = 0;
  while (Dijkstra(s, t)) {
    memcpy(pot, dist, sizeof dist);
    int pushed = INFL;
    for (int u = t; u != s; u = edges[pr[u]].u) {
      pushed = min(pushed, edges[pr[u]].cap - edges[pr[u]].flow);
    }
    for (int u = t; u != s; u = edges[pr[u]].u) {
      ans += pushed * edges[pr[u]].cost;
      edges[pr[u]].flow += pushed;
      edges[pr[u] ^ 1].flow -= pushed;
    }
  }
  return ans;
}

void run() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, cap, cost;
    cin >> u >> v >> cap >> cost;
    u--, v--;
    add_edge(u, v, cap, cost);
  }
  cout << min_cost_max_flow(0, n - 1) << '\n';
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



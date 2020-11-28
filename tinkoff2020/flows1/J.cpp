//
// Created by watemus on 13.11.2020.
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

vec<Edge> edges;
vec<int> g[N];

void add_edge(int u, int v, int cap, int cost) {
  g[u].push_back(edges.size());
  edges.push_back({u, v, 0, cap, cost});
  g[v].push_back(edges.size());
  edges.push_back({v, u, 0, 0, -cost});
}

int pot[N];
int q[N * N];
int in_q[N];

void Ford_Bellman(int s, int t) {
  fill(pot, pot + N, INFL);
  memset(in_q, 0, sizeof in_q);
  int qf = 0;
  int qs = 1;
  q[qf] = s;
  in_q[s] = 1;
  pot[s] = 0;
  while (qf < qs) {
    int u = q[qf++];
    for (auto id : g[u]) {
      auto &e = edges[id];
      if (pot[e.u] + e.cost < pot[e.v] && e.flow < e.cap) {
        pot[e.v] = pot[e.u] + e.cost;
        if (!in_q[e.v]) {
          q[qs++] = e.v;
          in_q[e.v] = 1;
        }
      }
    }
    in_q[u] = 0;
  }
}

int dist[N];
int pr[N];
int usd[N];

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
  int ans = 0;
  Ford_Bellman(s, t);
  while (Dijkstra(s, t)) {
    memcpy(pot, dist, sizeof dist);
    int pushed = INFL;
    for (int u = t; u != s; u = edges[pr[u]].u) {
      pushed = min(pushed, edges[pr[u]].cap - edges[pr[u]].flow);
    }
    for (int u = t; u != s; u = edges[pr[u]].u) {
      edges[pr[u]].flow += pushed;
      edges[pr[u] ^ 1].flow -= pushed;
      ans += pushed * edges[pr[u]].cost;
    }
  }
  return ans;
}

void run() {
  int n, k;
  cin >> n >> k;
  int s = k * 2;
  int t = k * 2 + 1;
  for (int i = 0; i < k; i++) {
    add_edge(s, i, 1, 0);
    add_edge(i + k, t, 1, 0);
  }
  string ss, tt;
  cin >> ss >> tt;
  map<int, int> ccnt;
  map<pair<int, int>, int> cnt;
  auto to = [](char ch) -> int {
    if ('A' <= ch && ch <= 'Z')
      return 26 + (ch - 'A');
    return ch - 'a';
  };
  auto from = [](int val) -> char {
    if (val >= 26)
      return char('A' + val - 26);
    return char('a' + val);
  };
  for (int i = 0; i < n; i++) {
    cnt[{to(ss[i]), to(tt[i])}]++;
  }
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k; j++) {
      add_edge(i, j + k, 1, -cnt[{i, j}]);
    }
  }
  int flow = min_cost_max_flow(s, t);
  cout << -flow << '\n';
  vec<int> ans(k);
  for (auto &e : edges) {
    if (e.u < 2 * k && e.v < 2 * k && e.flow == 1) {
      ans[e.u] = e.v - k;
    }
  }
  for (int i = 0; i < k; i++) {
    cout << from(ans[i]);
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



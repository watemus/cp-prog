//
// Created by watemus on 16.11.2020.
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

const int N = 150'010;

vec<pair<int, int>> g[N];

int sz[N], pr[N], usd[N], dist[N];

int get(int v) {
  if (pr[v] == -1)
    return v;
  return pr[v] = get(pr[v]);
}

void unite(int u, int v) {
  u = get(u);
  v = get(v);
  if (u == v)
    return;
  if (sz[v] > sz[u])
    swap(u, v);
  pr[v] = u;
  sz[u] += sz[v];
}

void run() {
  memset(pr, -1, sizeof pr);
  memset(usd, -1, sizeof usd);
  fill(sz, sz + N, 1);
  fill(dist, dist + N, INFL);
  int n, m, k, s;
  cin >> n >> m >> k >> s;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[u].emplace_back(v, c);
    g[v].emplace_back(u, c);
  }
  set<tuple<int, int, int>> st;
  vec<int> ks;
  for (int i = 0; i < k; i++) {
    int v;
    cin >> v;
    v--;
    ks.push_back(v);
    st.emplace(0, v, v);
    dist[v] = 0;
  }
  while (st.size()) {
    auto [dst, u, p] = *st.begin();
    st.erase(st.begin());
    if (usd[u] != -1) {
      continue;
    }
    usd[u] = p;
    for (auto [v, cost] : g[u]) {
      if (usd[v] != -1 && dist[v] + dist[u] + cost <= s) {
        unite(usd[u], usd[v]);
      } else if (usd[v] == -1 && dist[u] + cost <= s && dist[u] + cost < dist[v]) {
        dist[v] = min(dist[u] + cost, dist[v]);
        st.emplace(dist[v], v, p);
      }
    }
  }
  set<pair<int, int>> st2;
  memset(usd, 0, sizeof usd);
  fill(dist, dist + N, INFL);
  for (auto i : ks) {
    if (get(i) == get(0)) {
      st2.emplace(0, i);
      dist[i] = 0;
    }
  }
  vec<int> ans;
  while (st2.size()) {
    auto [dst, u] = *st2.begin();
    st2.erase(st2.begin());
    if (usd[u])
      continue;
    usd[u] = 1;
    ans.push_back(u + 1);
    for (auto [v, c] : g[u]) {
      if (!usd[v] && dist[u] + c <= s && dist[u] + c < dist[v]) {
        dist[v] = dist[u] + c;
        st2.emplace(dst + c, v);
      }
    }
  }
  cout << ans.size() << '\n';
  sort(ALL(ans));
  for (auto v : ans) {
    cout << v << ' ';
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



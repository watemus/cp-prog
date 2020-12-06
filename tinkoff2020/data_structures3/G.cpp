//
// Created by watemus on 03.12.2020.
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

// #define int ll

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

const int N = 2e5 + 10;
const int T = 6e7 + 10;

vec<pair<int, int>> g[N];
int anc[N];
int sz[N];
int roots[N];
int usd[N];
unordered_map<int, int> dist[N];

int calc_sz(int u, int p) {
  sz[u] = 1;
  for (auto [v, w] : g[u]) {
    if (!usd[v] && v != p) {
      sz[u] += calc_sz(v, u);
    }
  }
  return sz[u];
}

int find_centroid(int u, int p, int all_sz) {
  for (auto [v, w] : g[u]) {
    if (!usd[v] && v != p && sz[v] > all_sz / 2) {
      return find_centroid(v, u, all_sz);
    }
  }
  return u;
}

void calc_dist(int u, int p, ll dep, int center) {
  dist[center][u] = dep;
  for (auto [v, w] : g[u]) {
    if (!usd[v] && v != p && dep + w < INFI) {
      calc_dist(v, u, dep + w, center);
    }
  }
}

void make_decomp(int u, int p) {
  int all_sz = calc_sz(u, u);
  u = find_centroid(u, u, all_sz);
  anc[u] = p;
  usd[u] = 1;
  calc_dist(u, u, 0, u);
  for (auto [v, w] : g[u]) {
    if (!usd[v]) {
      make_decomp(v, u);
    }
  }
}

set<pair<int, int>> st[N];

int get(int u, int at) {
  int ans = 0;
  int uu = u;
  while (u != -1) {
    if (dist[u].count(uu) && at - dist[u][uu] >= 0) {
      auto it = st[u].upper_bound(pair(at - dist[u][uu], INFI + 10));
      if (it == st[u].begin()) {
        u = anc[u];
        continue;
      }
      it = prev(it);
      ans = max(ans, it->second);
    }
    u = anc[u];
  }
  return ans;
}

void add_event(int u, int at, int x) {
  int uu = u;
  while (u != -1) {
    if (dist[u].count(uu)) {
      auto it = st[u].lower_bound(pair(at + dist[u][uu], -INFI));
      while (it != st[u].end() && it->second <= x) {
        st[u].erase(it);
        it = st[u].lower_bound(pair(at + dist[u][uu], -INFI));
      }
      if (it == st[u].begin() || prev(it)->second < x) {
        st[u].insert(pair(at + dist[u][uu], x));
      }
    }
    u = anc[u];
  }
}

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  make_decomp(0, -1);
  int m;
  cin >> m;
  vec<pair<int, int>> events(m);
  for (auto &[d, c] : events) {
    cin >> c >> d;
    c--;
  }
  sort(ALL(events));
  int ans = 0;
  for (auto &[d, c] : events) {
    int cur = get(c, d);
    ans = max(ans, cur + 1);
    add_event(c, d, cur + 1);
  }
  cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
//  freopen("events.in", "r", stdin);
//  freopen("events.out", "w", stdout);
#endif
  int t = 1;
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



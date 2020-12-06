//
// Created by watemus on 02.12.2020.
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

const int N = 1e5 + 10;

vec<int> g[N];
unordered_map<int, int> dist[N];
unordered_map<int, int> cls[N];

int anc[N], clr[N];

int usd[N], sz[N];

int calc_sz(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (!usd[v] && v != p) {
      sz[u] += calc_sz(v, u);
    }
  }
  return sz[u];
}

int find_centroid(int u, int p, int all_sz) {
  for (auto v : g[u]) {
    if (v != p && !usd[v] && sz[v] > all_sz / 2) {
      return find_centroid(v, u, all_sz);
    }
  }
  return u;
}

void calc_ans(int u, int p, int center, int dep) {
  if (cls[center].count(clr[u])) {
    cls[center][clr[u]] = min(cls[center][clr[u]], dep);
  } else {
    cls[center][clr[u]] = dep;
  }
  dist[center][u] = dep;
  for (auto v : g[u]) {
    if (v != p && !usd[v]) {
      calc_ans(v, u, center, dep + 1);
    }
  }
}

void decomp(int u, int p) {
  int all_sz = calc_sz(u, u);
  u = find_centroid(u, u, all_sz);
  usd[u] = 1;
  anc[u] = p;
  calc_ans(u, u, u, 0);
  usd[u] = 1;
  for (auto v : g[u]) {
    if (!usd[v]) {
      decomp(v, u);
    }
  }
}

int get(int u, int c) {
  int ans = INFL;
  int v = u;
  while (u != -1) {
    if (cls[u].count(c)) {
      ans = min(ans, dist[u][v] + cls[u][c]);
    }
    u = anc[u];
  }
  return ans;
}

void run() {
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u;
    cin >> u;
    g[u].push_back(i);
    g[i].push_back(u);
  }
  for (int i = 0; i < n; i++) {
    cin >> clr[i];
  }
  decomp(0, -1);
  int q;
  cin >> q;
  while (q--) {
    int u, c;
    cin >> u >> c;
    int res = get(u, c);
    cout << (res == INFL ? -1 : res) << ' ';
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



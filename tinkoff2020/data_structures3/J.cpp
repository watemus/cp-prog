//
// Created by watemus on 05.12.2020.
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

const int N = 2e5 + 10;

int qr[N];

int szz = 0;

int ask(int x) {
  cout << "? " << szz << ' ' << x + 1 << ' ';
  for (int i = 0; i < szz; i++) {
    cout << qr[i] + 1 << ' ';
  }
  cout << endl;
  int ans = 0;
  cin >> ans;
  return ans;
}


vec<int> g[N];

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

void dfs(int u, int p) {
  qr[szz++] = u;
  for (auto v : g[u]) {
    if (!usd[v] && v != p) {
      dfs(v, u);
    }
  }
}


int make_decomp(int u) {
  int all_sz = calc_sz(u, u);
  if (all_sz == 1) {
    return u;
  }
  u = find_centroid(u, u, all_sz);
  vec<int> vc;
  vec<int> adj;
  szz = 0;
  for (auto v : g[u]) {
    if (!usd[v]) {
      adj.push_back(v);
      dfs(v, u);
    }
  }
  int res = ask(u);
  if (res)
    return u;
  int l = 0;
  int r = adj.size();
  calc_sz(u, u);
  while (l + 1 < r) {
    all_sz = 0;
    for (int i = l; i < r; i++) {
      all_sz += sz[adj[i]];
    }
    int mid = l;
    int mid_size = sz[adj[l]];
    while (mid_size < all_sz / 2) {
      mid++;
      mid_size += sz[adj[mid]];
    }
    szz = 0;
    for (int i = l; i <= mid; i++) {
      dfs(adj[i], u);
    }
    res = ask(u);
    if (res) {
      l = mid + 1;
    } else {
      r = mid + 1;
    }
  }
  usd[u] = 1;
  return make_decomp(adj[l]);
}

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int ans = make_decomp(0);
  cout << "! " << ans + 1 << endl;
}

signed main() {
#ifdef LOCAL
//  std::freopen("input.txt", "r", stdin);
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



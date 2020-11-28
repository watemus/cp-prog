//
// Created by watemus on 28.11.2020.
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

const int N = 2e5;
const int LOG_N = 20;

vec<int> g[N];
int up[LOG_N][N];
int h[N];

void make_up(int u, int p) {
  up[0][u] = p;
  for (int i = 1; i < LOG_N; i++) {
    up[i][u] = up[i - 1][up[i - 1][u]];
  }
  for (auto v : g[u]) {
    if (v != p) {
      h[v] = h[u] + 1;
      make_up(v, u);
    }
  }
}

int anc(int u, int hh) {
  for (int i = LOG_N - 1; i >= 0; i--) {
    if (hh >= (1 << i)) {
      u = up[i][u];
      hh -= (1 << i);
    }
  }
  return u;
}

int lca(int u, int v) {
  if (h[v] > h[u])
    swap(u, v);
  u = anc(u, h[u] - h[v]);
  if (u == v)
    return u;
  for (int i = LOG_N - 1; i >= 0; i--) {
    if (up[i][u] != up[i][v]) {
      u = up[i][u];
      v = up[i][v];
    }
  }
  return up[0][v];
}

void run() {
  int n, m;
  while (true) {
    cin >> n;
    if (n == 0)
      return;
    fill(g, g + n, vec<int>());
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    h[0] = 0;
    make_up(0, 0);
    int root = 0;
    cin >> m;
    while (m--) {
      char q;
      cin >> q;
      if (q == '!') {
        int v;
        cin >> v;
        v--;
        root = v;
      } else {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int a = lca(u, v);
        int b = lca(u, root);
        int c = lca(v, root);
        cout << (lca(u, v) ^ lca(u, root) ^ lca(v, root)) + 1 << '\n';
      }
    }
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



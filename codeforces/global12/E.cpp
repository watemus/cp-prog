//
// Created by watemus on 06.12.2020.
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

const int N = 210;

vec<pair<int, int>> g[N];

int d[N][N];

bool bipartite = true;

int usd[N];

void check_bipartite(int u, int col) {
  usd[u] = col;
  for (auto [v, w] : g[u]) {
    if (!usd[v]) {
      check_bipartite(v, 3 - col);
    } else if (usd[u] == usd[v]) {
      bipartite = false;
    }
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      d[i][j] = INFI;
    }
  }
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int u, v, b;
    cin >> u >> v >> b;
    u--, v--;
    g[u].emplace_back(v, 1);
    g[v].emplace_back(u, 1);
    if (b == 0) {
      d[u][v] = 1;
      d[v][u] = 1;
    } else {
      d[u][v] = 1;
      d[v][u] = -1;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
      }
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
      }
    }
  }
  check_bipartite(0, 1);
  bool have_neg_cycles = false;
  for (int i = 0; i < n; i++) {
    if (d[i][i] < 0) {
      have_neg_cycles = true;
      break;
    }
  }
  if (have_neg_cycles || !bipartite) {
    cout << "NO\n";
    return;
  }
  int a, b;
  a = b = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (d[i][j] > d[a][b]) {
        a = i;
        b = j;
      }
    }
  }
  cout << "YES\n";
  cout << d[a][b] << '\n';
  for (int i = 0; i < n; i++) {
    cout << d[a][i] + 1000 << ' ';
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



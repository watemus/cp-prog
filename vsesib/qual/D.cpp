//
// Created by watemus on 18.10.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 1e5 + 10;

vec<int> g[N], rg[N];
int typ[N];
int k[N], b[N];

vec<int> tsort;
int usd[N];

const int mod = 1e9 + 9;
void dfs(int v) {
  usd[v] = 1;
  int bb = 1;
  for (auto u : rg[v]) {
    if (!usd[u])
      dfs(u);
    if (typ[v] == 1) {
      if (k[u] != 0) {
        k[v] = k[u] * bb;
        k[v] %= mod;
        bb *= b[u];
        bb %= mod;
      } else {
        bb *= b[u];
        bb %= mod;
        k[v] *= b[u];
        k[v] %= mod;
      }
    } else if (typ[v] == 2) {
      k[v] += k[u];
      b[v] += b[u];
      k[v] %= mod;
      b[v] %= mod;
    }
  }
  if (typ[v] == 1) {
    b[v] = bb;
  }
  tsort.push_back(v);
}


void run() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++) {
    string tp;
    cin >> tp;
    if (tp == "*") {
      typ[i] = 1;
    } else if (tp == "+") {
      typ[i] = 2;
    } else if (tp == "x") {
      typ[i] = 3;
      k[i] = 1;
    } else {
      typ[i] = 4;
      b[i] = stoll(tp);
    }
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  for (int i = 0; i < n; i++) {
    if (!usd[i])
      dfs(i);
  }
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    cout << (x * k[0] % mod + b[0]) % mod << '\n';
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



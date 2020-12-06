//
// Created by watemus on 01.12.2020.
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

int val[N], anc[N];
vec<int> g[N];

int subtree_get(int u) {
  int ans = val[u];
  for (auto v : g[u]) {
    if (v != anc[u]) {
      ans += subtree_get(v);
    }
  }
  return ans;
}

int way_get(int u) {
  int ans = 0;
  while (u != -1) {
    ans += val[u];
    u = anc[u];
  }
  return ans;
}

void subtree_modify(int u, int x) {
  val[u] += x;
  for (auto v : g[u]) {
    if (v != anc[u]) {
      subtree_modify(v, x);
    }
  }
}

void way_modify(int u, int x) {
  while (u != -1) {
    val[u] += x;
    u = anc[u];
  }
}

const int MOD = 1e9 + 7;

void run() {
  int n, m;
  cin >> n >> m;
  anc[0] = -1;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u;
    v = i;
    anc[v] = u;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 0; i < n; i++) {
    cin >> val[i];
  }
  cout << val[n - 1] << ' ';
  while (m--) {
    int u, v;
    cin >> u >> v;
    int s = (subtree_get(u) + way_get(anc[u])) % MOD;
    subtree_modify(v, s);
    way_modify(anc[v], s);
    cout << val[n - 1] << ' ';
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



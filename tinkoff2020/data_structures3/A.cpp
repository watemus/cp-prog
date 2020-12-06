//
// Created by watemus on 30.11.2020.
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
int n, m;

namespace graph {

  vec<int> g[N];

  int sz[N], anc[N];

  void make_sz(int u, int p) {
    sz[u] = 1;
    anc[u] = p;
    for (auto v : g[u]) {
      if (v != p) {
        make_sz(v, u);
        sz[u] += sz[v];
      }
    }
    for (auto &v : g[u]) {
      if (v != p && sz[v] > sz[g[u][0]]) {
        swap(v, g[u][0]);
      }
    }
  }

  int tin[N], tout[N];
  int tin_pos[N];
  int dfs_timer = 0;
  int start[N];

  void make_euler(int u, int p, int cur_start) {
    tin_pos[dfs_timer] = u;
    tin[u] = dfs_timer++;
    start[u] = cur_start;
    bool was = false;
    for (auto v : g[u]) {
      if (v != p) {
        if (!was) {
          make_euler(v, u, cur_start);
        } else {
          make_euler(v, u, v);
        }
        was = true;
      }
    }
    tout[u] = dfs_timer;
  }

  bool is_anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }
}  // namespace graph

const int MOD = 1e9 + 7;

namespace seg_tree {
  int t[N * 4], agn[N * 4];
  void build(int v, int l, int r, vec<int> &arr) {
    if (r - l == 1) {
      t[v] = arr[l];
      agn[v] = 0;
    } else {
      int mid = (l + r) / 2;
      build(v * 2 + 1, l, mid, arr);
      build(v * 2 + 2, mid, r, arr);
      t[v] = (t[v * 2 + 1] + t[v * 2 + 2]);
      agn[v] = 0;
    }
  }
  void push(int v, int l, int r) {
    t[v] += agn[v] * (r - l);
    if (r - l > 1) {
      agn[v * 2 + 1] += agn[v];
      agn[v * 2 + 2] += agn[v];
    }
    agn[v] = 0;
  }
  void modify(int v, int l, int r, int lq, int rq, int x) {
    push(v, l, r);
    if (lq <= l && r <= rq) {
      agn[v] += x;
      push(v, l, r);
    } else if (rq <= l || r <= lq) {
      return;
    } else {
      int mid = (l + r) / 2;
      modify(v * 2 + 1, l, mid, lq, rq, x);
      modify(v * 2 + 2, mid, r, lq, rq, x);
      t[v] = (t[v * 2 + 1] + t[v * 2 + 2]);
    }
  }
  int get(int v, int l, int r, int lq, int rq) {
    push(v, l, r);
    if (lq <= l && r <= rq) {
      return t[v];
    } else if (rq <= l || r <= lq) {
      return 0;
    } else {
      int ans = 0;
      int mid = (l + r) / 2;
      ans += get(v * 2 + 1, l, mid, lq, rq);
      ans += get(v * 2 + 2, mid, r, lq, rq);
      return ans;
    }
  }
}  // namespace seg_tree

namespace graph {
  int sum_subtree(int u) {
    return seg_tree::get(0, 0, n, tin[u], tout[u]) % MOD;
  }
  void modify_subtree(int u, int x) {
    seg_tree::modify(0, 0, n, tin[u], tout[u], x);
  }
  int sum_way(int u) {
    int ans = 0;
    u = anc[u];
    while (u != -1) {
      ans += seg_tree::get(0, 0, n, tin[start[u]], tin[u] + 1);
      ans %= MOD;
      u = anc[start[u]];
    }
    return ans;
  }
  void modify_way(int u, int x) {
    u = anc[u];
    while (u != -1) {
      seg_tree::modify(0, 0, n, tin[start[u]], tin[u] + 1, x);
      u = anc[start[u]];
    }
  }
}  // namespace graph

void run() {
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u;
    v = i;
    graph::g[u].push_back(v);
    graph::g[v].push_back(u);
  }
  graph::make_sz(0, -1);
  graph::make_euler(0, -1, 0);
  vec<int> c(n), rc(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  for (int i = 0; i < n; i++) {
    rc[i] = c[graph::tin_pos[i]];
  }
  seg_tree::build(0, 0, n, rc);
  cout << seg_tree::get(0, 0, n, graph::tin[n - 1], graph::tin[n - 1] + 1) << ' ';
//  int tm = m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    int s = (graph::sum_subtree(u) + graph::sum_way(u)) % MOD;
//    for (int i = 0; i < n; i++) {
//      cerr << seg_tree::get(0, 0, n, graph::tin[i], graph::tin[i] + 1) << ' ';
//    }
//    cerr << endl;
    graph::modify_way(v, s);
//    for (int i = 0; i < n; i++) {
//      cerr << seg_tree::get(0, 0, n, graph::tin[i], graph::tin[i] + 1) << ' ';
//    }
//    cerr << endl;
    graph::modify_subtree(v, s);
//    for (int i = 0; i < n; i++) {
//      cerr << seg_tree::get(0, 0, n, graph::tin[i], graph::tin[i] + 1) << ' ';
//    }
//    cerr << endl;
    cout << seg_tree::get(0, 0, n, graph::tin[n - 1], graph::tin[n - 1] + 1) << ' ';
  }
  cout << '\n';
//  int cr = 1;
//  cout << cr << ' ';
//  while (tm--) {
//    cr += cr * 3  % MOD;
//    cout << cr << ' ';
//  }
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



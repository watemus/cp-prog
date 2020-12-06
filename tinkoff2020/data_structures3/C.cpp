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

const int N = 5e5 + 10;

vec<pair<int, int>> g[N];

int n;

int dist[N];
int tin[N], tout[N];
int dfs_timer = 0;

void calc_dist(int u) {
  tin[u] = dfs_timer++;
  for (auto [v, len] : g[u]) {
    dist[v] = dist[u] + len;
    calc_dist(v);
  }
  if (!g[u].empty())
    dist[u] = INFL;
  tout[u] = dfs_timer;
}


namespace seg_tree {
  int t[N * 4], agn[N * 4];
  void build(int v, int l, int r) {
    if (r - l == 1) {
      t[v] = dist[l];
      agn[v] = 0;
    } else {
      int mid = (l + r) / 2;
      build(v * 2 + 1, l, mid);
      build(v * 2 + 2, mid, r);
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
      agn[v] = 0;
    }
  }
  void push(int v, int l, int r) {
    t[v] += agn[v];
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
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
  }
  int get(int v, int l, int r, int lq, int rq) {
    push(v, l, r);
    if (lq <= l && r <= rq) {
      return t[v];
    } else if (rq <= l || r <= lq) {
      return INFL;
    } else {
      int ans = INFL;
      int mid = (l + r) / 2;
      ans = min(ans, get(v * 2 + 1, l, mid, lq, rq));
      ans = min(ans, get(v * 2 + 2, mid, r, lq, rq));
      return ans;
    }
  }
  void print(int v, int l, int r) {
    push(v, l, r);
    if (r - l == 1) {
      cerr << t[v] << ' ';
    } else {
      int mid = (l + r) / 2;
      print(v * 2 + 1, l, mid);
      print(v * 2 + 2, mid, r);
    }
  }
}  // namespace seg_tree

vec<tuple<int, int, int>> queries[N];
int ans[N];

void dfs(int u) {
  for (auto [l, r, i] : queries[u]) {
    ans[i] = seg_tree::get(0, 0, n, l - 1, r);
  }
//  seg_tree::print(0, 0, n);
//  cerr << endl;
  for (auto [v, w] : g[u]) {
//    cerr << tin[v] << ' ' << tout[v] << endl;
    seg_tree::modify(0, 0, n, 0, tin[v], w);
    seg_tree::modify(0, 0, n, tin[v], tout[v], -w);
    seg_tree::modify(0, 0, n, tout[v], dfs_timer, w);
    dfs(v);
    seg_tree::modify(0, 0, n, 0, tin[v], -w);
    seg_tree::modify(0, 0, n, tin[v], tout[v], w);
    seg_tree::modify(0, 0, n, tout[v], dfs_timer, -w);
  }
}

void run() {
  int q;
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    int anc, len;
    cin >> anc >> len;
    g[anc - 1].emplace_back(i, len);
  }
  calc_dist(0);
  seg_tree::build(0, 0, n);
  for (int i = 0; i < q; i++) {
    int v, l, r;
    cin >> v >> l >> r;
    v--;
    queries[v].emplace_back(l, r, i);
  }
  dfs(0);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
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



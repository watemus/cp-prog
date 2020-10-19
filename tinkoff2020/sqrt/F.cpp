//
// Created by watemus on 11.10.2020.
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

const int BLOCK = 300;
const int MO = 300;

struct Sqrt_dec {
  vec<int> t, tb;
  explicit Sqrt_dec(int n) : t(n), tb(n) {}
  void add(int p) {
    if (p >= t.size()) return;
    t[p]++;
    if (t[p] == 1)
      tb[p / BLOCK]++;
  }
  void rem(int p) {
    if (p >= t.size()) return;
    t[p]--;
    if (t[p] == 0)
      tb[p / BLOCK]--;
  }
  int get_mex() {
    int ans = 0;
    while (tb[ans] == BLOCK) ans++;
    ans *= BLOCK;
    while (t[ans]) ans++;
    return ans;
  }
};

struct Query {
  int l, r, id;
};

const int N = 1e5 + 10;

struct Edge {
  int v, c, id;
};

vec<Edge> g[N];

vec<pair<int, int>> euler_path;
int tin[N];

void make_euler_path(int v, int p) {
  for (auto [u, c, id] : g[v]) {
    if (u != p) {
      euler_path.emplace_back(c, id);
      tin[u] = euler_path.size() - 1;
      make_euler_path(u, v);
      euler_path.emplace_back(c, id);
    }
  }
}

void run() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    g[u].push_back({v, c, i});
    g[v].push_back({u, c, i});
  }
  make_euler_path(0, -1);
  tin[0] = -1;
  vec<Query> queries(q);
  int cntt = 0;
  for (auto &[l, r, id] : queries) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    if (tin[u] > tin[v]) {
      swap(u, v);
    }
    l = tin[u] + 1;
    r = tin[v];
    id = cntt++;
  }
  sort(ALL(queries), [](const Query &a, const Query &b) {
    return tuple(a.l / MO, a.r) < tuple(b.l / MO, b.r);
  });
  vec<int> cnt(n);
  Sqrt_dec sd(n * 3);
  auto add = [&](int p) {
    if (cnt[euler_path[p].second] == 0)
      sd.add(euler_path[p].first);
    else
      sd.rem(euler_path[p].first);
    cnt[euler_path[p].second]++;
  };
  auto rem = [&](int p) {
    if (cnt[euler_path[p].second] == 2)
      sd.add(euler_path[p].first);
    else
      sd.rem(euler_path[p].first);
    cnt[euler_path[p].second]--;
  };
  int lc, rc;
  lc = rc = 0;
  add(0);
  vec<int> ans(q);
  for (auto [lq, rq, id] : queries) {
    while (rc < rq) {
      rc++;
      add(rc);
    }
    while (lc > lq) {
      lc--;
      add(lc);
    }
    while (rc > rq) {
      rem(rc);
      rc--;
    }
    while (lc < lq) {
      rem(lc);
      lc++;
    }
    ans[id] = sd.get_mex();
  }
  for (auto el : ans) {
    cout << el << '\n';
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



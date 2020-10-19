//
// Created by watemus on 30.09.2020.
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

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

const int MAXN = 3e5;

vec<int> g[MAXN];
int pr[MAXN], sz[MAXN], a[MAXN], b[MAXN];

int cnt_v = 0;
int add_v() {
  return cnt_v++;
}

vec<tuple<int, int, int>> es;

void add_edge(int u, int v, int c) {
  es.emplace_back(c, u, v);
  es.emplace_back(c, v, u);
}

void dsu_init() {
  fill(sz, sz + MAXN, 1);
  fill(pr, pr + MAXN, -1);
}

int d_get(int v) {
  if (pr[v] == -1)
    return v;
  return pr[v] = d_get(pr[v]);
}

void d_unite(int u, int v) {
  u = d_get(u);
  v = d_get(v);
  if (u == v)
    return;
  if (sz[u] < sz[v])
    swap(u, v);
  pr[v] = u;
  sz[u] += sz[v];
}

void run() {
  int n, m;
  cin >> m >> n;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vec<int> tmp(n);
  for (int i = 0; i < n; i++) {
    tmp[i] = add_v();
  }
  int all = 0;
  dsu_init();
  for (int i = 0; i < m; i++) {
    int sz = 0;
    cin >> sz;
    vec<int> vs(sz);
    for (int j = 0; j < sz; j++) {
      int el;
      cin >> el;
      el--;
      vs[j] = add_v();
      add_edge(vs[j], tmp[el], -a[i] - b[el]);
      all += a[i] + b[el];
    }
    for (int j = 1; j < sz; j++) {
      d_unite(vs[j - 1], vs[j]);
    }
  }
  sort(ALL(es));
  for (auto [c, u, v] : es) {
    if (d_get(u) != d_get(v)) {
      all += c;
      d_unite(u, v);
    }
  }
  cout << all << '\n';
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



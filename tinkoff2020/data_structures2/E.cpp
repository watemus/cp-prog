//
// Created by watemus on 25.10.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'069;
constexpr int INFI = 1'000'000'069;
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

const int N = 1 << 19;

int pr[N], sz[N];
vec<pair<int, int>> st;

void dsu_init() {
  fill(sz, sz + N, 1);
  memset(pr, -1, sizeof pr);
}

int get(int v) {
  while (pr[v] != -1) {
    v = pr[v];
  }
  return v;
}

int cnt_comp;

void unite(int u, int v) {
  u = get(u);
  v = get(v);
  if (u == v) {
    st.emplace_back(-1, -1);
  } else {
    if (sz[u] < sz[v]) swap(u, v);
    pr[v] = u;
    sz[u] += sz[v];
    st.emplace_back(u, v);
    cnt_comp--;
  }
}

void rollback() {
  auto [u, v] = st.back();
  st.pop_back();
  if (u == -1)
    return;
  pr[v] = -1;
  sz[u] -= sz[v];
  cnt_comp++;
}

vec<pair<int, int>> t[N * 2];

void add(int v, int l, int r, int lq, int rq, pair<int, int> edge) {
  if (lq <= l && r <= rq) {
    t[v].push_back(edge);
  } else {
    int mid = (l + r) / 2;
    if (lq < mid)
      add(v * 2, l, mid, lq, rq, edge);
    if (mid < rq)
      add(v * 2 + 1, mid, r, lq, rq, edge);
  }
}

int ans[N];
bool good[N];

void solve(int v, int l, int r) {
  for (auto edge : t[v]) {
    unite(edge.first, edge.second);
  }
  if (r - l == 1 && good[l]) {
    ans[l] = cnt_comp;
  } else if (r - l > 1) {
    int mid = (l + r) / 2;
    solve(v * 2, l, mid);
    solve(v * 2 + 1, mid, r);
  }
  for (auto edge : t[v]) {
    rollback();
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  cnt_comp = n;
  dsu_init();
  map<pair<int, int>, int> mp;
  for (int i = 0; i < m; i++) {
    char q;
    cin >> q;
    if (q == '+') {
      int u, v;
      cin >> u >> v;
      u--, v--;
      if (u > v)
        swap(u, v);
      mp[{u, v}] = i;
    } else if (q == '-') {
      int u, v;
      cin >> u >> v;
      u--, v--;
      if (u > v)
        swap(u, v);
      add(1, 0, N, mp[{u, v}], i + 1, {u, v});
      mp.erase({u, v});
    } else {
      good[i] = 1;
    }
  }
  for (auto [uv, l] : mp) {
    add(1, 0, N, l, N, uv);
  }
  solve(1, 0, N);
  for (int i = 0; i < m; i++) {
    if (good[i])
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



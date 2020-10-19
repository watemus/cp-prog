//
// Created by watemus on 07.10.2020.
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

struct rect {
  int x1, y1, x2, y2;
};

struct shot {
  int x, y, c;
};

const int N = 6e5 + 10;

vec<pair<int, int>> st[N * 4];

void add(int v, int l, int r, int lq, int rq, int id, int time) {
  if (lq <= l && r <= rq) {
    st[v].emplace_back(time, id);
  } else {
    int mid = (l + r) / 2;
    if (lq < mid)
      add(v * 2 + 1, l, mid, lq, rq, id, time);
    if (mid < rq)
      add(v * 2 + 2, mid, r, lq, rq, id, time);
  }
}

void rem(int v, int l, int r, int lq, int rq) {
  if (lq <= l && r <= rq) {
    st[v].pop_back();
  } else {
    int mid = (l + r) / 2;
    if (lq < mid)
      rem(v * 2 + 1, l, mid, lq, rq);
    if (mid < rq)
      rem(v * 2 + 2, mid, r, lq, rq);
  }
}

pair<int, int> get(int v, int l, int r, int at, pair<int, int> cur) {
  if (st[v].size() && st[v].back().first > cur.first) {
    cur = st[v].back();
  }
  if (r - l == 1)
    return cur;
  int mid = (l + r) / 2;
  if (at < mid)
    return get(v * 2 + 1, l, mid, at, cur);
  else
    return get(v * 2 + 2, mid, r, at, cur);
}

vec<int> g[N];
set<int> sts[N];
int ans[N], usd[N];

void dfs(int v) {
  int mu = -1;
  usd[v] = 1;
  for (auto u : g[v]) {
    if (!usd[u])
      dfs(u);
    if (mu == -1 || sts[u].size() > sts[mu].size()) {
      mu = u;
    }
  }
  if (mu != -1 && sts[mu].size() > sts[v].size()) {
    swap(sts[v], sts[mu]);
  }
  for (auto u : g[v]) {
    {
      for (auto c : sts[u]) {
        sts[v].insert(c);
      }
    }
  }
  ans[v] = sts[v].size();
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<rect> rects(n);
  vec<int> coords_x, coords_y;
  for (auto &[x1, y1, x2, y2] : rects) {
    cin >> x1 >> y1 >> x2 >> y2;
    coords_x.push_back(x1);
    coords_x.push_back(x2);
    coords_y.push_back(y1);
    coords_y.push_back(y2);
  }
  vec<shot> shots(m);
  for (auto &[x, y, c] : shots) {
    cin >> x >> y >> c;
    coords_x.push_back(x);
    coords_y.push_back(y);
  }
  sort(ALL(coords_x));
  sort(ALL(coords_y));
  coords_x.resize(unique(ALL(coords_x)) - coords_x.begin());
  coords_y.resize(unique(ALL(coords_y)) - coords_y.begin());
  map<int, int> to_x, to_y;
  for (int i = 0; i < coords_x.size(); i++) {
    to_x[coords_x[i]] = i;
  }
  for (int i = 0; i < coords_y.size(); i++) {
    to_y[coords_y[i]] = i;
  }
  for (auto &[x1, y1, x2, y2] : rects) {
    x1 = to_x[x1];
    x2 = to_x[x2];
    y1 = to_y[y1];
    y2 = to_y[y2];
  }
  for (auto &[x, y, c] : shots) {
    x = to_x[x];
    y = to_y[y];
  }
  vec<vec<tuple<int, int, int>>> begs(coords_x.size()), ends(coords_x.size());
  vec<vec<pair<int, int>>> shots_sl(coords_x.size());
  for (int i = 0; i < n; i++) {
    begs[rects[i].x1].emplace_back(rects[i].y1, rects[i].y2, i);
    ends[rects[i].x2].emplace_back(rects[i].y1, rects[i].y2, i);
  }
  for (int i = 0; i < m; i++) {
    shots_sl[shots[i].x].emplace_back(shots[i].y, shots[i].c);
  }
  int times = 0;
  for (int x = 0; x < coords_x.size(); x++) {
    for (auto [y1, y2, id] : begs[x]) {
      pair<int, int> cr = {-INFI, -INFI};
      auto pr = get(0, 0, coords_y.size(), y1, cr);
      if (pr.second != -INFI) {
        g[pr.second].push_back(id);
      }
      add(0, 0, coords_y.size(), y1, y2 + 1, id, times);
      times++;
    }
    for (auto [y, c] : shots_sl[x]) {
      pair<int, int> cr = {-INFI, -INFI};
      auto pr = get(0, 0, coords_y.size(), y, cr);
      if (pr.second != -INFI) {
        sts[pr.second].insert(c);
      }
    }
    for (auto [y1, y2, id] : ends[x]) {
      rem(0, 0, coords_y.size(), y1, y2 + 1);
    }
  }
  for (int i = 0; i < n; i++) {
    if (!usd[i])
      dfs(i);
  }
  for (int i = 0; i < n; i++) {
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



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

const int BLOCK = 300;
const int MO = 1000;

struct sqrt_dec {
  vec<int> t, tb;
  explicit sqrt_dec(int n) : t(n), tb(n) {
    t[0] = 1;
    tb[0] = 1;
  }
  void add(int at) {
    t[at]++;
    if (t[at] == 1)
      tb[at / BLOCK]++;
  }
  void rem(int at) {
    t[at]--;
    if (t[at] == 0)
      tb[at / BLOCK]--;
  }
  int get_mex() {
    int i = 0;
    while (tb[i] == BLOCK) i++;
    i *= BLOCK;
    while (t[i]) i++;
    return i;
  }
};

struct Query {
  int l, r, t, id;
};

struct Mod {
  int p, x, nx;
};
void run() {
  int n, q;
  cin >> n >> q;
  vec<int> t_arr(n);
  vec<int> coords;
  for (int i = 0; i < n; i++) {
    cin >> t_arr[i];
    coords.push_back(t_arr[i]);
  }
  auto arr = t_arr;
  vec<Query> queries;
  vec<Mod> mods;
  for (int i = 0; i < q; i++) {
    int typ;
    cin >> typ;
    if (typ == 1) {
      int l, r;
      cin >> l >> r;
      l--, r--;
      queries.push_back({l, r, (int)mods.size(), i});
    } else {
      int p, x;
      cin >> p >> x;
      p--;
      mods.push_back({p, t_arr[p], x});
      coords.push_back(x);
      t_arr[p] = x;
    }
  }
  sort(ALL(coords));
  coords.resize(unique(ALL(coords)) - coords.begin());
  map<int, int> to_coords;
  for (int i = 0; i < coords.size(); i++) {
    to_coords[coords[i]] = i;
  }
  for (auto &x : arr) {
    x = to_coords[x];
  }
  for (auto &[p, x, nx] : mods) {
    x = to_coords[x];
    nx = to_coords[nx];
  }
  vec<int> sz(coords.size());
  sort(ALL(queries), [](const Query &a, const Query &b) {
    return tuple(a.l / MO, a.r / MO, a.t) < tuple(b.l / MO, b.r / MO, b.t);
  });
  sqrt_dec sd(n + 10);
  auto add = [&](int pos) {
    if (sz[arr[pos]] > 0)
      sd.rem(sz[arr[pos]]);
    sz[arr[pos]]++;
    sd.add(sz[arr[pos]]);
  };
  auto rem = [&](int pos) {
    sd.rem(sz[arr[pos]]);
    sz[arr[pos]]--;
    if (sz[arr[pos]] > 0)
      sd.add(sz[arr[pos]]);
  };
  auto modify = [&](int old, int nw) {
    sd.rem(sz[old]);
    sz[old]--;
    if (sz[old] > 0)
      sd.add(sz[old]);
    if (sz[nw] > 0)
      sd.rem(sz[nw]);
    sz[nw]++;
    sd.add(sz[nw]);
  };
  int lc, rc, tc;
  lc = rc = tc = 0;
  add(0);
  vec<int> ans(q, -1);
  for (auto [lq, rq, tq, id] : queries) {
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
    while (tc < tq) {
      int p = mods[tc].p;
      int nw = mods[tc].nx;
      int old = mods[tc].x;
      arr[p] = nw;
      if (lc <= p && p <= rc) {
        modify(old, nw);
      }
      tc++;
    }
    while (tc > tq) {
      tc--;
      int p = mods[tc].p;
      int nw = mods[tc].x;
      int old = mods[tc].nx;
      arr[p] = nw;
      if (lc <= p && p <= rc) {
        modify(old, nw);
      }
    }
    ans[id] = sd.get_mex();
  }
  for (auto el : ans) {
    if (el != -1) {
      cout << el << '\n';
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



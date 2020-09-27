//
// Created by watemus on 27.09.2020.
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

struct Treap {
    int sz, val, y, mx;
    Treap *lt = nullptr, *rt = nullptr;
    Treap(int val) : val(val), y(rnd()), sz(1), mx(val) {};
    };

int size(Treap *t) {
  if (t)
    return t->sz;
  return 0;
}

int max(Treap *t) {
  if (t)
    return t->mx;
  return -INFI;
}

void upd(Treap *t) {
  if (t) {
    t->sz = 1 + size(t->lt) + size(t->rt);
    t->mx = max({t->val, max(t->lt), max(t->rt)});
  }
}

pair<Treap*, Treap*> split(Treap *t, int sz) {
  if (!t)
    return {nullptr, nullptr};
  if (size(t->lt) >= sz) {
    auto [l, r] = split(t->lt, sz);
    upd(l);
    upd(r);
    t->lt = r;
    upd(t);
    return {l, t};
  } else {
    auto [l, r] = split(t->rt, sz - size(t->lt) - 1);
    upd(l);
    upd(r);
    t->rt = l;
    upd(t);
    return {t, r};
  }
}

Treap *merge(Treap *l, Treap *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->rt = merge(l->rt, r);
    upd(l->rt);
    upd(l);
    return l;
  } else {
    r->lt = merge(l, r->lt);
    upd(r->lt);
    upd(r);
    return r;
  }
}

int upd_mn(Treap *t) {
  if (t->val == t->mx) {
    int ans = t->val;
    t->val = 0;
    upd(t);
    return ans;
  } else if (max(t->lt) == t->mx) {
    int ans = upd_mn(t->lt);
    upd(t);
    return ans;
  } else {
    int ans = upd_mn(t->rt);
    upd(t);
    return ans;
  }
}

struct DSU {
  vec<int> pr, sz;
  vec<Treap*> d;
  int get(int v) {
    if (pr[v] == -1) {
      return v;
    }
    return pr[v] = get(pr[v]);
  }
  void unite(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v)
      return;
    if (sz[v] > sz[u])
      swap(u, v);
    pr[v] = u;
    sz[u] += sz[v];
    d[u] = merge(d[u], d[v]);
  }
  DSU(vec<int> &p) : pr(p.size(), -1), sz(p.size(), 1) {
    for (long long i : p) {
      d.push_back(new Treap(i));
    }
  }
};

void run() {
  int n, m, q;
  cin >> n >> m >> q;
  vec<int> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }
  DSU d(p);
  vec<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    edges[i] = {u, v};
  }
  vec<pair<int, int>> qs(q);
  vec<int> ban(m);
  for (auto &[x, y] : qs) {
    cin >> x >> y;
    if (x == 2) {
      ban[y - 1] = 1;
    }
  }
  reverse(ALL(qs));
  vec<int> ans;
  for (int i = 0; i < m; i++) {
    if (!ban[i]) {
      d.unite(edges[i].first, edges[i].second);
    }
  }
  for (auto )
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



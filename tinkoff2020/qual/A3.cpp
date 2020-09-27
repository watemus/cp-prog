//
// Created by watemus on 23.08.2020.
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

//#define int ll
//#define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(1);

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct DSU {
  vec<int> pr, sz;
  DSU(int n) : pr(n, -1), sz(n, 1) {}
  int get(int v) {
    if (pr[v] == -1)
      return v;
    return pr[v] = get(pr[v]);
  }
  bool merge(int u, int v) {
    u = get(u);
    v = get(v);
    if (u == v)
      return false;
    if (sz[u] < sz[v]) swap(u, v);
    pr[v] = u;
    sz[u] += sz[u];
    return true;
  }
};

struct Pivo {
  int color;
  int min_dist, c_dist;
  int prior;
  int id;
  int sz;
  Pivo *left = nullptr;
  Pivo *right = nullptr;
  Pivo(int color, int dist, int id)
  : color(color), min_dist(dist), c_dist(dist), prior(rnd()), id(id), sz(1) {}
};

inline int min_dist(Pivo *t) {
  if (t)
    return t->min_dist;
  return INFI;
}

inline int size(Pivo *t) {
  if (t)
    return t->sz;
  return 0;
}

inline void upd(Pivo *t) {
  if (t) {
    t->min_dist = min({t->c_dist, min_dist(t->left), min_dist(t->right)});
    t->sz = 1 + size(t->left) + size(t->right);
  }
}

pair<Pivo*, Pivo*> split_color(Pivo *t, int color) {
  if (!t)
    return {nullptr, nullptr};
  if (t->color > color) {
    auto [l, r] = split_color(t->left, color);
    upd(l);
    upd(r);
    t->left = r;
    upd(t);
    return {l, t};
  } else {
    auto [l, r] = split_color(t->right, color);
    upd(l);
    upd(r);
    t->right = l;
    upd(t);
    return {t, r};
  }
}

pair<Pivo*, Pivo*> split_id(Pivo *t, int id) {
  if (!t)
    return {nullptr, nullptr};
  if (t->id > id) {
    auto [l, r] = split_id(t->left, id);
    upd(l);
    upd(r);
    t->left = r;
    upd(t);
    return {l, t};
  } else {
    auto [l, r] = split_id(t->right, id);
    upd(l);
    upd(r);
    t->right = l;
    upd(t);
    return {t, r};
  }
}

Pivo *merge(Pivo *l, Pivo *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->prior > r->prior) {
    l->right = merge(l->right, r);
    upd(l->right);
    upd(l);
    return l;
  } else {
    r->left = merge(l, r->left);
    upd(r->left);
    upd(r);
    return r;
  }
}

struct Segment_tree {
  vec<int> t, base;
  int n;
  Segment_tree(int n) : n(n), t(n * 4), base(n)
  {
  }
  void modify(int v, int lb, int rb, int at, int val) {
    if (rb - lb == 1) {
      t[v] = val;
      base[lb] = val;
    } else {
      int mid = (lb + rb) / 2;
      if (at < mid) {
        modify(v * 2 + 1, lb, mid, at, val);
      } else {
        modify(v * 2 + 2, mid, rb, at, val);
      }
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
  }
  int get() {
    return t[0];
  }
};

void run() {
  int n, m, d, q;
  cin >> n >> m >> d >> q;
  vec<tuple<int, int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    edges.emplace_back(c, u, v);
  }
  sort(ALL(edges));
  DSU dsu(n);
  vec<vec<pair<int, int>>> g(n);
  for (auto [c, u, v] : edges) {
    if (dsu.merge(u, v)) {
      g[u].emplace_back(c, v);
      g[v].emplace_back(c, u);
    }
  }
  vec<int> colors(n);
  for (int i = 0; i < n; i++) {
    cin >> colors[i];
  }
  vec<Pivo*> pivos(n);
  vec<int> anc(n);
  Segment_tree st(n);
  vec<int> tsort;
  function<void(int, int)> make_pivos = [&](int v, int p) {
    anc[v] = p;
    vec<tuple<int, int, int>> v_pivos;
    for (auto [dist, u] : g[v]) {
      if (u != p) {
        make_pivos(u, v);
        v_pivos.emplace_back(u, colors[u], dist);
      }
    }
    sort(ALL(v_pivos));
    for (auto [u, color, dist] : v_pivos) {
      pivos[v] = merge(pivos[v], new Pivo(0, dist, u));

    }
    tsort.push_back(v);
  };
  make_pivos(0, -1);
  auto chg_color = [&](int v, int prev_col, int new_col) {
    int dist = INFI;
    auto [l, mr] = split_color(pivos[v], new_col - 1);
    auto [m, r] = split_color(mr, new_col);
    dist = min(min_dist(l), min_dist(r));
    pivos[v] = merge(l, merge(m, r));
    st.modify(0, 0, n, v, dist);
    if (anc[v] != -1) {
      int p = anc[v];
      tie(l, mr) = split_color(pivos[p], prev_col - 1);
      tie(m, r) = split_color(mr, prev_col);
      auto [ll, mmrr] = split_id(m, v - 1);
      auto [mm, rr] = split_id(mmrr, v);
      pivos[p] = merge(l, merge(ll, merge(rr, r)));
      mm->color = new_col;
      tie(l, mr) = split_color(pivos[p], new_col - 1);
      tie(m, r) = split_color(mr, new_col);
      tie(ll, rr) = split_id(m, v - 1);
      pivos[p] = merge(l, merge(ll, merge(mm, merge(rr, r))));
      tie(l, mr) = split_color(pivos[p], colors[p] - 1);
      tie(m, r) = split_color(mr, colors[p]);
      st.modify(0, 0, n, p, min(min_dist(l), min_dist(r)));
      pivos[p] = merge(l, merge(m, r));
    }
  };
  for (int i : tsort) {
    int prev_col = 0;
    int new_col = colors[i];
    chg_color(i, prev_col, new_col);
  }
  vec<int> ans;
  for (int i = 0; i < q; i++) {
    int v, c;
    cin >> v >> c;
    v--;
    chg_color(v, colors[v], c);
    colors[v] = c;
    ans.push_back(st.get());
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



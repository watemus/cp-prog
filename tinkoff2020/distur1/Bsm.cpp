//
// Created by watemus on 08.10.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
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

struct Treap {
  int val;
  int prior;
  int size;
  Treap *left = nullptr;
  Treap *right = nullptr;
  Treap(int val) : val(val), prior(rnd()), size(1) {}
};

inline int size(Treap *t) {
  return (t ? t->size : 0);
}

inline void upd(Treap *t) {
  if (t) {
    t->size = 1 + size(t->left) + size(t->right);
  }
}

pair<Treap*, Treap*> split_key(Treap *t, int key) {
  if (!t) return {nullptr, nullptr};
  if (t->val > key) {
    auto pr = split_key(t->left, key);
    upd(pr.first);
    upd(pr.second);
    t->left = pr.second;
    upd(t);
    return {pr.first, t};
  } else {
    auto pr = split_key(t->right, key);
    upd(pr.first);
    upd(pr.second);
    t->right = pr.first;
    upd(t);
    return {t, pr.second};
  }
}

pair<Treap*, Treap*> split_size(Treap *t, int sz) {
  if (!t) return {nullptr, nullptr};
  if (sz <= size(t->left)) {
    auto pr = split_size(t->left, sz);
    upd(pr.first);
    upd(pr.second);
    t->left = pr.second;
    upd(t);
    return {pr.first, t};
  } else {
    auto pr = split_size(t->right, sz - size(t->left) - 1);
    upd(pr.first);
    upd(pr.second);
    t->right = pr.first;
    upd(t);
    return {t, pr.second};
  }
}

Treap *merge(Treap *l, Treap *r) {
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

const int N = 2e5 + 10;

int ans[N];

vec<int> g[N];
Treap *t[N];

void dfs(int v) {
  t[v] = new Treap(v);
  for (auto u : g[v]) {
    dfs(u);
    ans[v] += ans[u];
    bool swapped = false;
    if (t[u]->size > t[v]->size) {
      swap(t[u], t[v]);
      swapped = true;
    }
    while (size(t[u])) {
      if (swapped) {
        auto pr = split_size(t[u], size(t[u]) - 1);
        swap(pr.first, pr.second);
        t[u] = pr.second;
        auto lr = split_key(t[v], pr.first->val);
        if (swapped)
          ans[v] += size(lr.first);
        else
          ans[v] += size(lr.second);
        t[v] = merge(lr.first, merge(pr.first, lr.second));
      } else {
        auto pr = split_size(t[u], 1);
        t[u] = pr.second;
        auto lr = split_key(t[v], pr.first->val);
        if (swapped)
          ans[v] += size(lr.first);
        else
          ans[v] += size(lr.second);
        t[v] = merge(lr.first, merge(pr.first, lr.second));
      }
    }
  }
}

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int u;
      cin >> u;
      u--;
      g[i].push_back(u);
    }
  }
  dfs(0);
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
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



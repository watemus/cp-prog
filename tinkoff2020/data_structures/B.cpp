//
// Created by watemus on 05.10.2020.
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
std::mt19937 rnd(229);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
const int N = 4;
#else
const int N = 1 << 16;
#endif

struct Treap {
  int val;
  int prior;
  int sum;
  int size;
  Treap *left = nullptr;
  Treap *right = nullptr;
  Treap(int val)
  : val(val), prior(rnd()), sum(val) {}
};

inline int sum(Treap *t) {
  return (t ? t->sum : 0);
}

inline int size(Treap *t) {
  return (t ? t->size : 0);
}

inline void upd(Treap *t) {
  if (t) {
    t->sum = t->val + sum(t->left) + sum(t->right);
    t->size = 1 + size(t->left) + size(t->right);
  }
}

pair<Treap*, Treap*> split(Treap *t, int val) {
  if (!t)
    return {nullptr, nullptr};
  if (val < t->val) {
    auto [l, r] = split(t->left, val);
    upd(l);
    upd(r);
    t->left = r;
    upd(t);
    return {l, t};
  } else {
    auto [l, r] = split(t->right, val);
    upd(l);
    upd(r);
    t->right = l;
    upd(t);
    return {t, r};
  }
}

pair<Treap*, Treap*> split_sz(Treap *t, int sz) {
  if (!t)
    return {nullptr, nullptr};
  if (sz <= size(t->left)) {
    auto [l, r] = split_sz(t->left, sz);
    upd(l);
    upd(r);
    t->left = r;
    upd(t);
    return {l, t};
  } else {
    sz -= size(t->left) + 1;
    auto [l, r] = split_sz(t->right, sz);
    upd(l);
    upd(r);
    t->right = l;
    upd(t);
    return {t, r};
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


int a[N + 228];
Treap* t[N * 2 + 228];

void build(int v, int l, int r) {
  vec<int> sa;
  for (int i = l; i < r; i++) {
    sa.push_back(a[i]);
  }
  sort(ALL(sa));
  t[v] = new Treap(sa[0]);
  for (int i = 1; i < sa.size(); i++) {
    t[v] = merge(t[v], new Treap(sa[i]));
  }
  if (r - l > 1) {
    int mid = (l + r) >> 1;
    build(v * 2, l, mid);
    build(v * 2 + 1, mid, r);
  }
}

void modify(int x, int new_val) {
  int old_val = a[x];
  a[x] = new_val;
  x += N;
  t[x] = new Treap(new_val);
  x /= 2;
  while (x > 0) {
    auto [l, mr] = split(t[x], old_val - 1);
    auto [m, r] = split(mr, old_val);
    auto [lm, rm] = split_sz(m, size(m) - 1);
    t[x] = merge(l, merge(lm, r));
    tie(l, r) = split(t[x], new_val);
    t[x] = merge(l, merge(new Treap(new_val), r));
    x /= 2;
  }
}

pair<int, int> unite(pair<int, int> a, pair<int, int> b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

pair<int, int> get(int v, int l, int r, int lq, int rq, int y1, int y2) {
  if (lq <= l && r <= rq) {
    int lower = (y1 + y2) / 2;
    int upper = (y1 + y2) / 2;
    if ((y1 + y2) % 2 == 0) {
      lower--;
    }
    auto [lt, mr] = split(t[v], lower);
    auto [mt, rt] = split(mr, upper);
    pair<int, int> ans = {size(lt), size(rt)};
    t[v] = merge(lt, merge(mt, rt));
    return ans;
  } else {
    int mid = (l + r) >> 1;
    pair<int, int> ans = {0, 0};
    if (lq < mid)
      ans = unite(ans, get(v * 2, l, mid, lq, rq, y1, y2));
    if (mid < rq)
      ans = unite(ans, get(v * 2 + 1, mid, r, lq, rq, y1, y2));
    return ans;
  }
}

void run() {
  memset(a, -1, sizeof a);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  build(1, 0, N);
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    char ch;
    cin >> ch;
    if (ch == 'C') {
      int at, val;
      cin >> at >> val;
      at--;
      modify(at, val);
    } else {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      auto res = get(1, 0, N, x1 - 1, x2, y1, y2);
      if (res.first == res.second) {
        cout << "0\n";
      } else if (res.first > res.second) {
        cout << "1\n";
      } else {
        cout << "2\n";
      }
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



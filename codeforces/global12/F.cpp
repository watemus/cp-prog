//
// Created by watemus on 06.12.2020.
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

const int N = 1e5 + 10;

struct Pivo {
  int x, y, sz;
  Pivo *l, *r;
  Pivo(int val) : x(val), y(rnd()), sz(1), l(nullptr), r(nullptr) {}
};

int sz(Pivo *t) {
  if (t)
    return t->sz;
  return 0;
}

void upd(Pivo *t) {
  if (t) {
    t->sz = 1 + sz(t->l) + sz(t->r);
  }
}

pair<Pivo*, Pivo*> split(Pivo *t, int szz) {
  if (!t) return {nullptr, nullptr};
  if (sz(t->l) >= szz) {
    auto [l, r] = split(t->l, szz);
    upd(l);
    upd(r);
    t->l = r;
    upd(t);
    return {l, t};
  } else {
    auto [l, r] = split(t->r, szz - sz(t->l) - 1);
    upd(l);
    upd(r);
    t->r = l;
    return {t, r};
  }
}

Pivo *merge(Pivo *l, Pivo *r) {
  if (!l) return r;
  if (!r) return l;
  if (l->y > r->y) {
    l->r = merge(l->r, r);
    upd(l->r);
    upd(l);
    return l;
  } else {
    r->l = merge(l, r->l);
    upd(r->l);
    upd(r);
    return r;
  }
}

Pivo *st[N];

int fst(Pivo *p) {
  if (p->l)
    return fst(p->l);
  return p->x;
}

vec<int> ansik;

void print(Pivo *t) {
  if (!t)
    return;
  print(t->l);
  ansik.push_back(t->x);
  print(t->r);
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }
  fill(st, st + n, nullptr);
  for (int i = 0; i < n; i++) {
    st[a[i]] = merge(st[a[i]], new Pivo(i));
  }
  Pivo *ans = nullptr;
  for (int i = 0; i < n; i++) {
    if (sz(ans) < sz(st[i])) {
      swap(ans, st[i]);
    }
    if (sz(st[i]) == 0) continue;
    Pivo *pp = nullptr;
    if (fst(ans) < fst(st[i])) {
      tie(pp, ans) = split(ans, 1);
    }
    int ln = sz(st[i]);
    for (int j = 0; j < ln; j++) {
      Pivo *tt;
      tie(tt, st[i]) = split(st[i], 1);
      Pivo *ll, *rr;
      tie(ll, rr) = split(ans, 2 * j + 1);
      ans = merge(ll, merge(tt, rr));
    }
    ans = merge(pp, ans);
  }
  ansik.clear();
  int anss = 0;
  print(ans);
  for (int i = 0; i < n; i++) {
    cerr << a[ansik[i]] << ' ';
  }
  cerr << endl;
  cout << anss << '\n';
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
   cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



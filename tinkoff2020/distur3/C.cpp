//
// Created by watemus on 23.10.2020.
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

struct Pivo {
  int val;
  int prior;
  Pivo *left = nullptr;
  Pivo *right = nullptr;
  int sz = 1;
  bool rev = false;
  Pivo(int val) : val(val), prior(rnd()) {}
};

inline int size(Pivo *t) {
  return (t ? t->sz : 0);
}
inline void push(Pivo *t) {
  if (t) {
    if (t->rev) {
      swap(t->left, t->right);
      if (t->left)
        t->left->rev ^= 1;
      if (t->right)
        t->right->rev ^= 1;
      t->rev = 0;
    }
  }
}
inline void pull(Pivo *t) {
  if (t) {
    push(t->left);
    push(t->right);
    t->sz = size(t->left) + size(t->right) + 1;
  }
}



pair<Pivo*, Pivo*> split(Pivo* t, int sz) {
  if (!t) return {nullptr, nullptr};
  push(t);
  if (sz <= size(t->left)) {
    auto pr = split(t->left, sz);
    pull(pr.first);
    pull(pr.second);
    t->left = pr.second;
    pull(t);
    return {pr.first, t};
  } else {
    auto pr = split(t->right, sz - 1 - size(t->left));
    pull(pr.first);
    pull(pr.second);
    t->right = pr.first;
    pull(t);
    return {t, pr.second};
  }
}

Pivo *merge(Pivo *l, Pivo *r) {
  if (!l) return r;
  if (!r) return l;
  push(l);
  push(r);
  if (l->prior > r->prior) {
    l->right = merge(l->right, r);
    pull(l->right);
    pull(l);
    return l;
  } else {
    r->left = merge(l, r->left);
    pull(r->left);
    pull(r);
    return r;
  }
}

void print(Pivo *t) {
  if (!t) return;
  push(t);
  print(t->left);
  cout << t->val << ' ';
  print(t->right);
}

void run() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  int cnt = 0;
  Pivo *a = nullptr, *b = nullptr;
  for (auto ch : s) {
    if (ch == 'a') {
      cnt++;
      a = merge(a, new Pivo(cnt % 10));
    } else if (ch == 'b') {
      cnt++;
      b = merge(b, new Pivo(cnt % 10));
    } else if (ch == 'A') {
      auto pr = split(a, 1);
      cout << pr.first->val;
      a = pr.second;
    } else if (ch == 'B') {
      auto pr = split(b, 1);
      cout << pr.first->val;
      b = pr.second;
    } else if (ch == '>') {
      if (a) {
        a->rev ^= 1;
      }
      b = merge(b, a);
      a = nullptr;
    } else if (ch == ']') {
      if (b) {
        b->rev ^= 1;
      }
      a = merge(a, b);
      b = nullptr;
    } else if (ch == '<') {
      if (b != nullptr) {
        auto pr = split(b, (size(b) + 1) / 2);
        if (pr.second) {
          pr.second->rev ^= 1;
        }
        a = merge(a, pr.second);
        b = pr.first;
      }
    } else {
      if (a != nullptr) {
        auto pr = split(a, (size(a) + 1) / 2);
        if (pr.second) {
          pr.second->rev ^= 1;
        }
        b = merge(b, pr.second);
        a = pr.first;
      }
    }
//    print(a);
//    cout << endl;
//    print(b);
//    cout << endl;
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



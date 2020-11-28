//
// Created by watemus on 29.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

//#define int ll

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

const int N = (1 << 17) + 10;

int t[N];
ll sm[N];
int sz[N], prior[N], agn[N], lt[N], rt[N];

int cnt_nodes = 0;

inline int new_node(int val) {
  int v = cnt_nodes++;
  t[v] = val;
  prior[v] = rnd();
  agn[v] = 0;
  lt[v] = -1;
  rt[v] = -1;
  return v;
}

inline int size(int v) {
  return (v == -1 ? 0 : sz[v]);
}

inline ll sum(int v) {
  return (v == -1 ? 0 : sm[v] + sz[v] * agn[v]);
}

inline void push(int v) {
  if (v != -1) {
    sm[v] += agn[v] * sz[v];
    t[v] += agn[v];
    if (lt[v] != -1) agn[lt[v]] += agn[v];
    if (rt[v] != -1) agn[rt[v]] += agn[v];
    agn[v] = 0;
  }
}

inline void pull(int v) {
  if (v != -1) {
    sz[v] = 1 + size(lt[v]) + size(rt[v]);
    sm[v] = sum(lt[v]) + sum(rt[v]) + t[v];
  }
}

pair<int, int> split(int v, int key) {
  if (v == -1) return {-1, -1};
  push(v);
  if (key < t[v]) {
    auto [l, r] = split(lt[v], key);
    pull(l);
    pull(r);
    lt[v] = r;
    pull(v);
    return {l, v};
  } else {
    auto [l, r] = split(rt[v], key);
    pull(l);
    pull(r);
    rt[v] = l;
    pull(v);
    return {v, r};
  }
}

pair<int, int> split_sz(int v, int s) {
  if (v == -1) return {-1, -1};
  push(v);
  if (size(lt[v]) >= s) {
    auto [l, r] = split_sz(lt[v], s);
    pull(l);
    pull(r);
    lt[v] = r;
    pull(v);
    return {l, v};
  } else {
    auto [l, r] = split_sz(rt[v], s - size(lt[v]) - 1);
    pull(l);
    pull(r);
    rt[v] = l;
    pull(v);
    return {v, r};
  }
}

inline int order_of_key(int v, int key) {
  int ans = 0;
  while (true) {
    if (v == -1)
      break;
    push(v);
    if (key < t[v]) {
      v = lt[v];
    } else {
      ans += 1 + size(lt[v]);
      v = rt[v];
    }
  }
  return ans;
}

int merge(int l, int r) {
  if (l == -1) return r;
  if (r == -1) return l;
  push(l);
  push(r);
  if (prior[l] > prior[r]) {
    rt[l] = merge(rt[l], r);
    pull(rt[l]);
    pull(l);
    return l;
  } else {
    lt[r] = merge(l, lt[r]);
    pull(lt[r]);
    pull(r);
    return r;
  }
}

inline void add1(int v) {
  if (v != -1)
    agn[v]++;
}

inline void sub1(int v) {
  if (v != -1)
    agn[v]--;
}

void print(int v) {
  if (v == -1)
    return;
  push(v);
  print(lt[v]);
  cout << t[v] << ' ';
  print(rt[v]);
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  vec<int> sa(n);
  int left = -1;
  int right = -1;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sa[i] = a[i] + i;
  }
  sort(ALL(sa));
  for (auto el : sa) {
    right = merge(right, new_node(el));
  }
  ll ans = INFL;
  for (int i = 0; i < n; i++) {
    int l = max(i + 1, n - i) - 1;
    int r = INFI;
    while (l + 1 < r) {
      int mid = (l + r) / 2;
      int k1 = order_of_key(left, mid);
      int k2 = order_of_key(right, mid);
      if (k1 + k2 >= (n + 1) / 2) {
        r = mid;
      } else {
        l = mid;
      }
    }
    auto [l1, r1] = split(right, r);
    auto [l2, r2] = split(left, r);
    ans = min(ans, size(l1) * 1ll * r - sum(l1) + sum(r1) - size(r1) * 1ll * r +
                  size(l2) * 1ll * r - sum(l2) + sum(r2) - size(r2) * 1ll * r);
//    print(l1);
//    cout << endl;
//    print(r1);
//    cout << endl;//////
    right = merge(l1, r1);
    left = merge(l2, r2);
    auto [ll, mr] = split(right, a[i] - 1);
    auto [mm, rr] = split_sz(mr, 1);
    right = merge(ll, rr);
    sub1(right);
    tie(ll, rr) = split(left, a[i]);
    left = merge(ll, merge(mm, rr));
    add1(left);
  }
  cout << ans << '\n';
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




//
// Created by watemus on 04.08.2020.
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
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

struct Segment_tree {
  vec<int> t;
  int n;
  Segment_tree(int n, vec<int> &arr)
    : n(n), t(n * 4)
  {
    build(0, 0, n, arr);
  }
  void build(int v, int lb, int rb, vec<int> &arr) {
    if (rb - lb == 1) {
      t[v] = arr[lb];
    } else {
      int mid = (lb + rb) / 2;
      build(v * 2 + 1, lb, mid, arr);
      build(v * 2 + 2, mid, rb, arr);
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
  }
  int get(int v, int lb, int rb, int lq, int rq) {
    if (lq <= lb && rb <= rq) {
      return t[v];
    }
    int ans = INFI;
    int mid = (lb + rb) / 2;
    if (lq < mid)
      ans = min(ans, get(v * 2 + 1, lb, mid, lq, rq));
    if (mid < rq)
      ans = min(ans, get(v * 2 + 2, mid, rb, lq, rq));
    return ans;
  }
};

void run() {
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  vec<int> lt(q + 1, -1), rt(q + 1, -1);
  vec<int> begs(n), ends(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] > 0) {
      if (lt[a[i]] == -1) {
        lt[a[i]] = i;
      }
      rt[a[i]] = i;
    }
  }
  for (int i = 1; i <= q; i++) {
    if (lt[i] == -1) continue;
    begs[lt[i]]++;
    ends[rt[i]]++;
  }
  bool have_last = lt[q] != -1;
  if (!have_last) {
    for (int i = 0; i < n; i++) {
      if (a[i] == 0) {
        a[i] = q;
        lt[q] = rt[q] = i;
        have_last = true;
        break;
      }
    }
  }
  if (!have_last) {
    cout << "NO\n";
    return;
  }
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) a[i] = INFI;
  }
  Segment_tree t(n, a);
  for (int i = 1; i <= q; i++) {
    if (lt[i] == -1) continue;
    int mn = t.get(0, 0, n, lt[i], rt[i] + 1);
    if (mn < i) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
  for (int i = 1; i < n; i++) {
    if (a[i] == INFI) {
      a[i] = a[i - 1];
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    if (a[i] == INFI) {
      a[i] = a[i + 1];
    }
  }
  for (int i = 0; i < n; i++) {
    cout << a[i] << ' ';
  }
  cout << '\n';
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



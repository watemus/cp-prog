//
// Created by watemus on 22.11.2020.
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

const int N = 2e5;

int a[N * 4], suf[N * 4], pref[N * 4], ans[N * 4];

inline void pull(int v, int l, int r) {
  ans[v] = 1;
  if (r - l > 1) {
    pref[v] = pref[v * 2 + 1];
    suf[v] = suf[v * 2 + 2];
    ans[v] = max({ans[v], ans[v * 2 + 1], ans[v * 2 + 2]});
    int mid = (l + r) / 2;
    if (a[mid - 1] < a[mid]) {
      ans[v] = max({ans[v], suf[v * 2 + 1] + pref[v * 2 + 2]});
      if (pref[v * 2 + 1] == (mid - l)) {
        pref[v] += pref[v * 2 + 2];
      }
      if (suf[v * 2 + 2] == (r - mid)) {
        suf[v] += suf[v * 2 + 1];
      }
    }
  }
}

void build(int v, int l, int r) {
  if (r - l == 1) {
    suf[v] = pref[v] = 1;
    ans[v] = 1;
  } else {
    int mid = (l + r) / 2;
    build(v * 2 + 1, l, mid);
    build(v * 2 + 2, mid, r);
    pull(v, l, r);
  }
}

void modify(int v, int l, int r, int at) {
  if (r - l == 1) {
    return;
  } else {
    int mid = (l + r) / 2;
    if (at < mid) {
      modify(v * 2 + 1, l, mid, at);
    } else {
      modify(v * 2 + 2, mid, r, at);
    }
    pull(v, l, r);
  }
}

void run() {
  int n, q;
  cin >> n >> q;
  vec<int> p(n), rp(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    a[p[i] - 1] = i;
  }
  build(0, 0, n);
  cout << n - ans[0] << '\n';
  while (q--) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    swap(p[x], p[y]);
    a[p[x] - 1] = x;
    a[p[y] - 1] = y;
    modify(0, 0, n, p[x] - 1);
    modify(0, 0, n, p[y] - 1);
    cout << n - ans[0] << '\n';
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



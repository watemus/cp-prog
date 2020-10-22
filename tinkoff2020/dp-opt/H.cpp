//
// Created by watemus on 20.10.2020.
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

#define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'001;
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

const int N = 1 << 18;
const int T = 1.5e7;

signed t[N * 2 + 10];
int k[T], b[T];
signed lt[T], rt[T];

int cnt_nodes = 0;

inline int new_node() {
  return cnt_nodes++;
}

inline void __add_line(int v, int k1, int b1) {
  int l = 0;
  int r = INFI;
  while (true) {
    int mid = (l + r) / 2;
    int cx = k[v] * mid + b[v];
    int nx = k1 * mid + b1;
    if (nx < cx) {
      swap(k1, k[v]);
      swap(b1, b[v]);
    }
    if (l + 1 == r || b1 == INT64_MAX)
      break;
    int lc = k[v] * l + b[v];
    int ln = k1 * l + b1;
    if (ln < lc) {
      r = mid;
      if (lt[v] == -1)
        lt[v] = new_node();
      v = lt[v];
    } else {
      l = mid;
      if (rt[v] == -1)
        rt[v] = new_node();
      v = rt[v];
    }
  }
}

inline int __get(int v, int x) {
  int l = 0;
  int r = INFI;
  int ans = INT64_MAX;
  while (true) {
    ans = min(ans, k[v] * x + b[v]);
    int mid = (l + r) / 2;
    if (l + 1 == r)
      break;
    if (x < mid) {
      if (lt[v] == -1) {
        break;
      } else {
        v = lt[v];
      }
      r = mid;
    } else {
      if (rt[v] == -1) {
        break;
      } else {
        v = rt[v];
      }
      l = mid;
    }
  }
  return ans;
}

void build() {
  for (int v = 1; v < 2 * N; v++) {
    t[v] = new_node();
  }
}

inline void add_line(int v, int k1, int b1) {
  v += N;
  while (v > 0) {
    __add_line(t[v], k1, b1);
    v /= 2;
  }
}

int get(int l, int r, int x) {
  l += N;
  r += N;
  int ans = INT64_MAX;
  while (l < r) {
    if (l & 1) {
      ans = min(ans, __get(t[l], x));
      l++;
    }
    if (r & 1) {
      r--;
      ans = min(ans, __get(t[r], x));
    }
    l >>= 1;
    r >>= 1;
  }
  return ans;
}

signed x[N + 3], p[N + 3], a[N + 3];

void run() {
  fill(b, b + T, INT64_MAX);
  memset(lt, -1, sizeof lt);
  memset(rt, -1, sizeof rt);
  int n, m;
  cin >> n >> m;
  build();
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> p[i];
    add_line(i, -2 * 1ll * x[i], p[i] + x[i] * 1ll * x[i]);
  }
  for (int i = 0; i < m; i++) {
    int cx, c;
    cin >> cx >> c;
    for (int j = 0; j < c; j++) {
      cin >> a[j];
    }
    sort(a, a + c);
    if (c > 0) {
      int ans = INT64_MAX;
      if (a[0] > 0)
        ans = get(0, a[0], cx);
      for (int j = 1; j < c; j++) {
        if (a[j] - a[j - 1] > 1)
          ans = min(ans, get(a[j - 1] + 1, a[j], cx));
      }
      ans = min(ans, get(a[c - 1] + 1, N, cx));
      cout << ans + cx * cx << '\n';
    } else {
      cout << get(0, N, cx) + cx * cx << '\n';
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



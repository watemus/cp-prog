//
// Created by watemus on 16.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

#define int __int128

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

#ifdef LOCAL
#else
#endif

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

inline int lcm(int a, int b) {
  return a / gcd(a, b) * b;
}

inline int abss(int a) {
  return (a < 0 ? -a : a);
}
int ex_gcd(int a, int b, int *x, int *y) {
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }
  int x1, y1;
  int g = ex_gcd(b, a % b, &x1, &y1);
  *x = y1;
  *y = x1 - (a / b) * y1;
  return g;
}

inline pair<int, int> solve(int a, int b) {
  int x, y;
  ex_gcd(a, b, &x, &y);
  if (x < 0) {
    int cnt = abss(x) / b;
    x += (cnt + 1) * b;
    y -= (cnt + 1) * a;
  }
  int cnt = x / b;
  x -= cnt * b;
  y += cnt * a;
  if (x == 0) {
    x += b;
    y -= a;
  }
  y *= -1;
  return {x, y};
}

inline int read_int() {
  ll el;
  cin >> el;
  return el;
}


void run() {
  int n, m;
  n = read_int();
  m = read_int();
  set<int> st;
  for (int i = 0; i < m; i++) {
    int el = read_int();
    st.insert(el);
  }
  st.insert(n);
  vec<int> a {st.begin(), st.end()};
  int ans = 0;
  for (int mask = 1; mask < (1 << a.size()); mask++) {
    for (int mask2 = 1; mask2 < (1 << a.size()); mask2++) {
      if ((mask & mask2) && (a[0] != 1 || (mask & mask2) != 1))
        continue;
      int cans = 0;
      int lcm1 = 1, lcm2 = 1;
      bool correct = true;
      int c1 = 0;
      int c2 = 0;
      for (int i = 0; i < a.size(); i++) {
        if (mask & (1 << i)) {
          int g = gcd(lcm1, a[i]);
          lcm1 = (lcm1 * a[i]) / g;
          c1++;
        }
        if (mask2 & (1 << i)) {
          int g = gcd(lcm2, a[i]);
          lcm2 = (lcm2 * a[i]) / g;
          c2++;
        }
        if (lcm1 > n || lcm2 > n) {
          correct = false;
          break;
        }
      }
      if (!correct)
        continue;
      if (gcd(lcm1, lcm2) > 1)
        continue;
      auto [x, y] = solve(lcm1, lcm2);
      if (x * lcm1 <= n) {
        cans++;
        cans += (n - x * lcm1) / lcm(lcm1, lcm2);
      }
      if ((c1 + c2) & 1)
        ans -= cans;
      else
        ans += cans;
    }
  }
  cout << (ll)abss(ans) << '\n';
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



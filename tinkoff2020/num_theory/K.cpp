//
// Created by watemus on 27.09.2020.
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
using ull = unsigned long long;
using i128 = __int128;
using f128 = _Float128;

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

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

const double TL = 1.7;
inline bool is_tl() {
  static int is = 0, cnt = 0;
  {
    is |= clock() > (TL - 0.1) * CLOCKS_PER_SEC;
  }
  return is;
}

i128 read() {
  ull a;
  cin >> a;
  return a;
}

inline bool is_square(i128 n) {
  i128 dn = i128(sqrtf128(n));
  dn *= dn;
  return n == dn;
}

inline i128 gcd(i128 a, i128 b) {
  while (b ^= a ^= b ^= a %= b) {}
  return a;
}

i128 Lehman(i128 n) {
  f128 fn = n;
  i128 to_k = floorf128(powf128(fn, 1./3.));
  for (i128 k = 1; k <= to_k; k++) {
    i128 to_d = floorf128(powf128(n, 1./6.) / (sqrtf128(k) * 4)) + 1;
    for (i128 d = 0; d <= to_d; d++) {
      if (is_tl())
        return n;
      if (is_square(i128(floorf128(sqrtf128(k * n * 4)) + d) * i128(floorf128(sqrtf128(k * n * 4)) + d) - k * n * 4)) {
        i128 A = floorf128(sqrtf128(k * n * 4)) + d;
        i128 B = floorf128(sqrtf128(A * A - k * n * 4));
        if (1 < gcd(A + B, n) && gcd(A + B, n) < n) {
          return gcd(A + B, n);
        } else if (1 < gcd(A - B, n) && gcd(A - B, n) < n) {
          return gcd(A - B, n);
        }
      }
    }
  }
  return n;
}

void run() {
  int t;
  while (cin >> t) {
    cout << char(t);
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

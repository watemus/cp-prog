//
// Created by watemus on 30.09.2020.
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

void run() {
  int n;
  ld len;
  cin >> n >> len;
  vec<ld> a(n + 2), b(n + 2);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = len - a[i];
  }
  reverse(ALL(b));
  b[n + 1] = len;
  a[n + 1] = len;
  ld l = 0;
  ld r = 1e9  + 10;
  for (int iter = 0; iter < 100; iter++) {
    ld mid = (l + r) / 2;
    ld at0 = 0;
    ld cv0 = 1;
    ld ct = 0;
    ld dst0 = 0;
    for (int i = 1; i <= n + 1; i++) {
      if (ct + (a[i] - a[i - 1]) / cv0 <= mid) {
        ct += (a[i] - a[i - 1]) / cv0;
        cv0++;
        dst0 += a[i] - a[i - 1];
      } else {
        dst0 += (mid - ct) * cv0;
        break;
      }
    }
    ld at1 = 0;
    ld cv1 = 1;
    ld ct1 = 0;
    ld dst1 = 0;
    for (int i = 1; i <= n + 1; i++) {
      if (ct1 + (b[i] - b[i - 1]) / cv1 <= mid) {
        ct1 += (b[i] - b[i - 1]) / cv1;
        cv1++;
        dst1 += b[i] - b[i - 1];
      } else {
        dst1 += (mid - ct1) * cv1;
        break;
      }
    }
    if (dst1 + dst0 > len) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << fixed << setprecision(20);
  cout << l << '\n';
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



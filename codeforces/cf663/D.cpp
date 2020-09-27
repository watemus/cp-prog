//
// Created by watemus on 10.08.2020.
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

inline bool check(int pmask, int mask, int n) {
  if (n == 1) return 1;
  if (n == 2) {
    return (__builtin_popcount(pmask) + __builtin_popcount(mask)) % 2;
  } else {
    return (__builtin_popcount(pmask & 3) + __builtin_popcount(mask & 3)) % 2 && (__builtin_popcount(pmask & 6) + __builtin_popcount(mask & 6)) % 2;
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  if (n > 3 && m > 3) {
    cout << "-1\n";
    return;
  }
  vec<int> a;
  if (n > m) {
    a.resize(n);
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < m; j++) {
        if (s[j] == '1') {
          a[i] += (1 << j);
        }
      }
    }
  } else {
    a.resize(m);
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < m; j++) {
        if (s[j] == '1') {
          a[j] += (1 << i);
        }
      }
    }
    swap(n, m);
  }
  vec<vec<int>> dp(n, vec<int>(1 << m, INFI));
  for (int mask = 0; mask < (1 << m); mask++) {
    dp[0][mask] = __builtin_popcount(mask ^ a[0]);
  }
  for (int i = 1; i < n; i++) {
    for (int pmask = 0; pmask < (1 << m); pmask++) {
      if (dp[i - 1][pmask] == INFI) {
        continue;
      }
      for (int mask = 0; mask < (1 << m); mask++) {
        int cost = __builtin_popcount(mask ^ a[i]);
        if (check(pmask, mask, m)) {
          dp[i][mask] = min(dp[i][mask], dp[i - 1][pmask] + cost);
        }
      }
    }
  }
  int ans = INFI;
  for (int i = 0; i < (1 << m); i++) {
    ans = min(ans, dp.back()[i]);
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



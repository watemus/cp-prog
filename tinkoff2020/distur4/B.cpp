//
// Created by watemus on 29.10.2020.
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

const int N = 310;

int dp[N][N][N];

void run() {
  int n, m, k;
  cin >> n >> m >> k;
  vec<int> a(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fill(dp[i][j], dp[i][j] + N, INFL);
    }
  }
  for (int i = 0; i < N; i++) {
    dp[0][0][i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int shift = 0; shift < k; shift++) {
      dp[i][0][shift] = dp[i - 1][0][shift];
      if (i % k != 0) {
        dp[i][0][shift] += a[i];
      }
      for (int j = 1; j <= min(i, m); j++) {
        int pdp = dp[i - 1][j - 1][shift];
        if ((j + shift) % k != 0) pdp += a[i];
        int cdp = dp[i - 1][j][shift];
        if ((i - j) % k != 0) {
          cdp += a[i];
        }
        dp[i][j][shift] = min(cdp, pdp);
      }
    }
  }
  int ans = INFL;
  for (int i = 0; i <= m; i++) {
    ans = min(ans, dp[n][i][(n - i) % k]);
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



//
// Created by watemus on 14.08.2020.
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

void run() {
  int n, m, k;
  cin >> n >> m >> k;
  vec<int> a(n), b(m), c(k);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }
  for (int i = 0; i < k; i++) {
    cin >> c[i];
  }
  sort(RALL(a)), sort(RALL(b)), sort(RALL(c));
  vec<vec<vec<int>>> dp(n + 1, vec<vec<int>>(m + 1, vec<int>(k + 1)));
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      for (int h = 0; h <= k; h++) {
        if (min(i, 1LL) + min(j, 1LL) + min(h, 1LL) < 2) continue;
        if (i > 0)
          dp[i][j][h] = max(dp[i][j][h], dp[i - 1][j][h]);
        if (j > 0)
          dp[i][j][h] = max(dp[i][j][h], dp[i][j - 1][h]);
        if (h > 0)
          dp[i][j][h] = max(dp[i][j][h], dp[i][j][h - 1]);
        if (i > 0 && j > 0) {
          dp[i][j][h] = max(dp[i][j][h], dp[i - 1][j - 1][h] + a[i - 1] * b[j - 1]);
        }
        if (i > 0 && h > 0) {
          dp[i][j][h] = max(dp[i][j][h], dp[i - 1][j][h - 1] + a[i - 1] * c[h - 1]);
        }
        if (h > 0 && j > 0) {
          dp[i][j][h] = max(dp[i][j][h], dp[i][j - 1][h - 1] + c[h - 1] * b[j - 1]);
        }
      }
    }
  }
  cout << dp[n][m][k] << '\n';
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



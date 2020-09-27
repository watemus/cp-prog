//
// Created by watemus on 29.07.2020.
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
  int n, k, z;
  cin >> n >> k >> z;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vec<vec<array<int, 2>>> dp(n, vec<array<int, 2>>(z + 1));
  dp[0][0][0] = a[0];
  for (int i = 1; i < n; i++) {
    dp[i][0][1] = dp[i][0][0] = dp[i - 1][0][0] + a[i];
  }
  for (int j = 1; j <= z; j++) {
    for (int i = n - 2; i >= 0; i--) {
      dp[i][j][0] = dp[i + 1][j - 1][1] + a[i];
    }
    for (int i = 1; i < n; i++) {
      dp[i][j][1] = max(dp[i - 1][j][0], dp[i - 1][j][1]) + a[i];
     // cout << dp[i][j][1] << ":" << dp[i][j][0] << ", ";
    }
    //cout << endl;
  }
  int ans = 0;
  for (int i = 0; i <= z; i++) {
    if (k - 2 * i >= 0){
      ans = max(ans, dp[k - i * 2][i][1]);
      ans = max(ans, dp[k - i * 2][i][0]);
    }
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



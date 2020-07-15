//
// Created by watemus on 12.07.2020.
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

void run();

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


void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<pair<int, int>>> segs(n + 2, vec<pair<int, int>>(m + 2));
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    while (k--) {
      int lb, rb;
      cin >> lb >> rb;
      for (int j = lb; j <= rb; j++) {
        segs[i][j] = {lb, rb};
      }
    }
  }
  vec<vec<ll>> dp(m + 2, vec<ll>(m + 2));
  for (int i = m; i >= 1; i--) {
    for (int j = i; j <= m; j++) {
      for (int k = i; k <= j; k++) {
        int cur = 0;
        for (int h = 0; h < n; h++) {
          cur += (segs[h][k].first >= i && segs[h][k].second <= j);
        }
        dp[i][j] = max(dp[i][j], dp[i][k - 1] + cur * cur + dp[k + 1][j]);
      }
    }
  }
  cout << dp[1][m] << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/



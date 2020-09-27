//
// Created by watemus on 04.08.2020.
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

vec<pair<int, int>> DD {pair(1LL, 0LL), pair(-1LL, 0LL), pair(0LL, 1LL), pair(0LL, -1LL)};

#ifdef LOCAL
#else
#endif

void run() {
  int n, m;
  cin >> n >> m;
  vec<int> aggr(n), cost(n), income(n + m + 2);
  for (int i = 0; i < n; i++) {
    cin >> aggr[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> cost[i];
  }
  for (int i = 1; i <= n + m; i++) {
    cin >> income[i];
  }
  reverse(ALL(aggr));
  reverse(ALL(cost));
  vec<vec<int>> dp(n + m + 2, vec<int>(n + 1, -INFI));
  for (int i = 0; i <= n + m + 1; i++) {
    dp[i][0] = 0;
  }
  for (int i = 0; i < n; i++) {
    for (int cnt = n; cnt > 0; cnt--) {
      if (dp[aggr[i]][cnt - 1] == -INFI)
        continue;
      dp[aggr[i]][cnt] = max(dp[aggr[i]][cnt], dp[aggr[i]][cnt - 1] - cost[i] + income[aggr[i]]);
    }
    int max_cnt = n;
    for (int cur_aggr = aggr[i]; cur_aggr + 1 <= n + m + 1; cur_aggr++) {
      for (int cur_cnt = 0; cur_cnt <= max_cnt; cur_cnt++) {
        if (dp[cur_aggr][cur_cnt] == -INFI)
          continue;
        dp[cur_aggr + 1][cur_cnt / 2] = max(dp[cur_aggr + 1][cur_cnt / 2], dp[cur_aggr][cur_cnt] + (cur_cnt / 2) * income[cur_aggr + 1]);
      }
      max_cnt /= 2;
    }
  }
  cout << dp[n + m + 1][0] << '\n';
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

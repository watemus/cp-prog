//
// Created by watemus on 21.07.2020.
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
    int n, s, f;
    cin >> n >> s >> f;
    s--, f--;
    vec<vec<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    int len = 0;
    function<bool(int, int, int)> calc_len = [&](int v, int p, int dep) {
      if (v == f) {
        len = dep;
        return true;
      }
      for (auto u : g[v]) {
        if (u != p) {
          bool found = calc_len(u, v, dep + 1);
          if (found)
            return true;
        }
      }
      return false;
    };
    calc_len(s, s, 0);
    vec<vec<pair<int, int>>> dp(n, vec<pair<int, int>>(3, {-1, -1}));
    function<void(int, int)> calc_dp1 = [&](int v, int p) {
      for (auto u : g[v]) {
        if (u != p) {
          calc_dp1(u, v);
          dp[v].push_back(dp[u][0]);
          dp[v].back().first++;
        }
      }
      if (g[v].size() == 1) {
        dp[v].emplace_back(0, v);
      }
      sort(RALL(dp[v]));
      dp[v].resize(3);
    };
    function<void(int, int, pair<int, int>)> calc_dp2 = [&](int v, int p, pair<int, int> up) {
      up.first++;
      dp[v].push_back(up);
      sort(RALL(dp[v]));
      dp[v].resize(3);
      for (auto u : g[v]) {
        if (u != p) {
          if (dp[u][0].second == dp[v][0].second) {
            calc_dp2(u, v, dp[v][1]);
          } else {
            calc_dp2(u, v, dp[v][0]);
          }
        }
      }
    };
    calc_dp1(0, 0);
    calc_dp2(0, 0, {-1, -1});
    vec<int> pivots(n);
    int cnt_pivots = 0;
    for (int i = 0; i < n; i++) {
      bool is_pivot = true;
      for (int j = 0; j < 3; j++) {
        if (dp[i][j] < len) {
          is_pivot = false;
          break;
        }
      }
      if (is_pivot) {
        pivots[i] = 1;
        cnt_pivots++;
      }
    }
    if (cnt_pivots == 0) {
      cout << "NO\n";
      return;
    }
    const int LOGN = 20;
    vec<vec<int>> up(LOGN, vec<int>(n));
    auto up_pivots = up;
    function<void(int, int)> calc_up = [&](int v, int p) {
      up[0][v] = p;
      up_pivots[0][v] = pivots[v];
      for (int i = 1; i < LOGN; i++) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        up_pivots[i][v] = up_pivots[i - 1][v] + up_pivots[i - 1][up[i - 1][v]];
      }
      for (auto u : g[v]) {
        if (u != p) {
          calc_up(u, v);
          pivots[v] += pivots[u];
        }
      }
    };
    function<pair<int,int>(int, int)> anc = [&](int v, int h) {
      int cur_pivots = 0;
      for (int i = LOGN - 1; i >= 0; i--) {
        if (h >= (1 << i)) {
          cur_pivots += up_pivots[i][v];
          v = up[i][v];
          h -= (1 << i);
        }
      }
      return pair{v, cur_pivots};
    };
    for (int iter = 0; iter < n; iter++) {
      s = dp[s][0].second;
      auto [ff, pp] = anc(s, len);
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}



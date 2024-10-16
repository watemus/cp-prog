//
// Created by watemus on 20.10.2020.
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

// #define int ll

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

const int N = 4010;

int p[N][N];

inline int cost(int l, int r) {
  return (p[r][r] - p[l - 1][r] - p[r][l - 1] + p[l - 1][l - 1]) / 2;
}

int dp[N][N];
int opt[N][N];

void solve(int k, int l, int r, int opt_l, int opt_r) {
  if (r < l)
    return;
  int mid = (l + r) / 2;
  dp[k][mid] = INFI;
  for (int i = max(k - 1, opt_l); i <= min(opt_r, mid - 1); i++) {
    int cur_dp = dp[k - 1][i] + cost(i + 1, mid);
    if (cur_dp < dp[k][mid]) {
      dp[k][mid] = cur_dp;
      opt[k][mid] = i;
    }
  }
  solve(k, l, mid - 1, opt_l, opt[k][mid]);
  solve(k, mid + 1, r, opt[k][mid], opt_r);
}

void run() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> p[i][j];
      p[i][j] += p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1];
    }
  }
  for (int i = 1; i <= n; i++) {
    dp[1][i] = cost(1, i);
    opt[1][i] = 0;
  }
  for (int i = 2; i <= k; i++) {
    solve(i, i, n, 1, n + 1);
  }
  cout << dp[k][n] << '\n';
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



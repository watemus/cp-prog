//
// Created by watemus on 18.10.2020.
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
using ld = double;

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

const int N = 5e4 + 10;
const int K = 102;

ld dp[K][N];
int opt[K][N];

ld x[N], xp[N], xps[N];

inline ld cost(int l, int r) {
  ld p = (xp[r] - xp[l - 1]) / (r - l + 1);
  ld ans = (xps[r] - xps[l - 1]) - p * 2 * (xp[r] - xp[l - 1]) + (r - l + 1) * p * p;
  return ans;
}

void solve(int k, int l, int r, int opt_l, int opt_r) {
  if (r < l)
    return;
  int mid = (l + r) / 2;
  dp[k][mid] = INFL;
  for (int i = max(opt_l - 1, k - 1); i <= min(opt_r + 1, mid - 1); i++) {
    ld cr = dp[k - 1][i] + cost(i + 1, mid);
    if (cr < dp[k][mid]) {
      dp[k][mid] = cr;
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
    cin >> x[i];
  }
  sort(x, x + n + 1);
  for (int i = 1; i <= n; i++) {
    xp[i] = xp[i - 1] + x[i];
    xps[i] = xps[i - 1] + x[i] * x[i];
  }
  for (int i = 1; i <= n; i++) {
    dp[1][i] = cost(1, i);
    opt[1][i] = 0;
  }
  for (int i = 2; i <= k; i++) {
    solve(i, i, n, 1, n + 1);
  }
  cout << fixed << setprecision(20);
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



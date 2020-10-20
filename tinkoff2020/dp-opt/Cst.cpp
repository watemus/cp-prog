//
// Created by watemus on 19.10.2020.
//

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

#ifdef LOCAL
#else
#endif

const int N = 5e4 + 10;
const int K = 102;

ld dp[K][N];
int opt[K][N];

void run() {
  int n, k;
  cin >> n >> k;
  vec<ld> x(n + 1), xp(n + 1), xps(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }
  sort(ALL(x));
  for (int i = 1; i <= n; i++) {
    xp[i] = xp[i - 1] + x[i];
    xps[i] = xps[i - 1] + x[i] * x[i];
  }
  auto cost = [&](int l, int r) {
    ld p = (xp[r] - xp[l - 1]) / (r - l + 1);
    ld ans = (xps[r] - xps[l - 1]) - p * 2 * (xp[r] - xp[l - 1]) + (r - l + 1) * p * p;
    return ans;
  };
  for (int i = 1; i <= n; i++) {
    dp[1][i] = cost(1, i);
    opt[1][i] = 1;
  }
  for (int i = 2; i <= k; i++) {
    opt[i][n + 1] = n - 1;
    for (int j = n; j >= i; j--) {
      dp[i][j] = INFL;
      for (int h = i - 1; h <= j - 1; h++) {
        ld cr = dp[i - 1][h] + cost(h + 1, j);
        if (cr < dp[i][j]) {
          dp[i][j] = cr;
          opt[i][j] = h + 1;
        }
      }
    }
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


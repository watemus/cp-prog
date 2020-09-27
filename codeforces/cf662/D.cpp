//
// Created by watemus on 07.08.2020.
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
  int n, m;
  cin >> n >> m;
  vec<vec<char>> a(n, vec<char>(m));
  vec<vec<int>> dp1(n, vec<int>(m, 1));
  auto dp2 = dp1, dp3 = dp1, dp4 = dp1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      if (a[i][j] == a[i - 1][j] && a[i][j] == a[i][j - 1]) {
        dp1[i][j] = min(dp1[i - 1][j], dp1[i][j - 1]) + 1;
      }
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = m - 2; j >= 0; j--) {
      if (a[i][j] == a[i - 1][j] && a[i][j] == a[i][j + 1]) {
        dp2[i][j] = min(dp2[i - 1][j], dp2[i][j + 1]) + 1;
      }
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    for (int j = 1; j < m; j++) {
      if (a[i][j] == a[i + 1][j] && a[i][j] == a[i][j - 1]) {
        dp3[i][j] = min(dp3[i + 1][j], dp3[i][j - 1]) + 1;
      }
    }
  }
  for (int i = n - 2; i >= 0; i--) {
    for (int j = m - 2; j >= 0; j--) {
      if (a[i][j] == a[i + 1][j] && a[i][j] == a[i][j + 1]) {
        dp4[i][j] = min(dp4[i + 1][j], dp4[i][j + 1]) + 1;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans += min({dp1[i][j], dp2[i][j], dp3[i][j], dp4[i][j]});
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



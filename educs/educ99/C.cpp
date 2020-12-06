//
// Created by watemus on 30.11.2020.
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

//#define int ll

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

const int N = 510;

short dp[N][N][N];

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < N; j++) {
      fill(dp[i][j], dp[i][j] + N, (short) 1000);
    }
  }
  int x;
  cin >> x;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  dp[0][a[0]][x] = 0;
  if (a[0] > x) {
    dp[0][x][a[0]] = 1;
  }
  for (int i = 1; i < n; i++) {
    for (int xc = 0; xc < N; xc++) {
      for (int j = 0; j <= a[i]; j++) {
        dp[i][a[i]][xc] = min(dp[i][a[i]][xc], dp[i - 1][j][xc]);
      }
      if (a[i] > xc) {
        for (int j = 0; j <= xc; j++) {
          dp[i][xc][a[i]] = min((int) dp[i][xc][a[i]], dp[i - 1][j][xc] + 1);
        }
      }
    }
  }
  int ans = 1000;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      ans = min(ans, (int)dp[n - 1][i][j]);
    }
  }
  cout << (ans == 1000 ? -1 : ans) << '\n';
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



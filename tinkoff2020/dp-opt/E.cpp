//
// Created by watemus on 19.10.2020.
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

#define int __int128

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

const int N = 2e5 + 10;
const int LOG_N = 19;

int sp[LOG_N][N];
int a[N];
int lg[N];

int n;

void init_sp(int n) {
  lg[1] = 0;
  for (int i = 2; i <= n; i++) {
    lg[i] = lg[i / 2] + 1;
  }
  for (int i = 1; i <= n; i++) {
    sp[0][i] = a[i];
  }
  for (int i = 1; i < LOG_N; i++) {
    for (int j = 0; j + (1 << i) <= N; j++) {
      sp[i][j] = (sp[i - 1][j] | sp[i - 1][j + (1 << (i - 1))]);
    }
  }
}

inline int get(int l, int r) {
  int len = lg[r - l + 1];
  int ans = sp[len][l] | sp[len][r - (1 << len) + 1];
  return ans;
}

int dp[N];
int cnt[N];

void calc(int Y) {
  fill(dp, dp + N, -INFL);
  dp[0] = 0;
  cnt[0] = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < i; j++) {
      int ndp = dp[j] + get(j + 1, i) - Y;
      if (ndp > dp[i]) {
        dp[i] = ndp;
        cnt[i] = cnt[j] + 1;
      }
    }
  }
}

int rd() {
  ll el;
  cin >> el;
  return el;
}

void run() {
  int k;
  n = rd();
  k = rd();
  for (int i = 1; i <= n; i++) {
    a[i] = rd();
  }
  init_sp(n);
  int l = 0;
  int r = INT64_MAX;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    calc(mid);
    if (cnt[n] < k) {
      r = mid;
    } else {
      l = mid;
    }
  }
  calc(l);
  cout << ll(dp[n] + l * k) << '\n';
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



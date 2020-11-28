//
// Created by watemus on 15.11.2020.
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

const int MOD = 786433;
const int W = 3;
const int N = 1 << 16;
const int H = 16;

int pw(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
      ans %= MOD;
    }
    a *= a;
    a %= MOD;
    b >>= 1;
  }
  return ans;
}

int dp[H][N + 10];

void ntt(int *s, int *ans, int n, int t, int a, int b, int c) {
  if (n == 1) {
    ans[c] = s[a];
  } else {
    ntt(s, ans, n / 2, t * t % MOD, a, b * 2, c);
    ntt(s, ans, n / 2, t * t % MOD, a + b, b * 2, c + n / 2);
    int x = 1;
    for (int i = 0; i < n / 2; i++) {
      int an1 = ans[c + i];
      int an2 = ans[c + i + n / 2];
      ans[c + i] = (an1 + x * an2) % MOD;
      ans[c + i + n / 2] = ((an1 - x * an2) % MOD + MOD) % MOD;
      x = (x * t) % MOD;
    }
  }
}


int c1[N + 10];
int c2[N + 10];

void convolution(int *a, int *b, int *c) {
  ntt(a, c1, N, W, 0, 1, 0);
  ntt(b, c2, N, W, 0, 1, 0);
  for (int i = 0; i < N; i++) {
    c1[i] *= c2[i];
    c1[i] %= MOD;
  }
  ntt(c1, c, N, pw(W, MOD - 2), 0, 1, 0);
  int rev = pw(N, MOD - 2);
  for (int i = 0; i < N; i++) {
    c[i] = c[i] * rev % MOD;
  }
}

int tt[N + 10];

void run() {
  dp[0][1] = 1;
  dp[1][2] = 2;
  dp[1][3] = 1;
  for (int i = 2; i < H; i++) {
    convolution(dp[i - 1], dp[i - 1], tt);
    for (int j = 1; j < N; j++) {
      dp[i][j] += tt[j - 1];
    }
    convolution(dp[i - 1], dp[i - 2], tt);
    for (int j = 0; j < N; j++) {
      dp[i][j] += 2 * tt[j - 1];
      dp[i][j] %= MOD;
    }
  }
  int n, h;
  cin >> n >> h;
//  for (int i = 0; i <= h; i++) {
//    for (int j = 0; j <= n; j++) {
//      cout << dp[i][j] << ' ';
//    }
//    cout << endl;
//  }
  cout << dp[h][n] << '\n';
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



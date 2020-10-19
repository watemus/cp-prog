//
// Created by watemus on 13.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
#pragma comment(linker, "/STACK:256000000")
#pragma warning(disable:4996)
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

#ifdef LOCAL
#else
#endif

const double TL = 0.5;
inline bool is_tl() {
  static int is = 0, cnt = 0;
  {
    is |= clock() > (TL - 0.001) * CLOCKS_PER_SEC;
  }
  return is;
}

void run() {
  constexpr int N = 10;
  constexpr int STEPS = 7;
  constexpr int K = 100;
  constexpr int MOD = 1 << (STEPS * 2);
  int DD[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  char a[N][N];
  char f[N][N][MOD][N][N];

  int dp[N * N * MOD];
  int ndp[N * N * MOD];
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int el;
      cin >> el;
      a[i][j] = (char)el;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int h = 0; h < MOD; h++) {
        for (int g = 0; g < n; g++) {
          memcpy(f[i][j][h][g], a[g], sizeof a[g]);
        }
        int cx = i;
        int cy = j;
        int ch = h;
        int pw = 1;
        for (int iter = 0; iter < STEPS; iter++) {
          int cs = ch % 4;
          ch /= 4;
          cx -= DD[cs][0];
          cy -= DD[cs][1];
          if (cx < 0 || cy < 0 || cx >= n || cy >= m)
            continue;
          f[i][j][h][cx][cy] = min((int)a[cx][cy], pw);
          pw = min(max(1, pw * 2), 101);
        }
      }
    }
  }
  fill(dp, dp + N * N * MOD, -INFI);
  fill(ndp, ndp + N * N * MOD, -INFI);
  dp[0] = a[0][0];
  ll ans = a[0][0];
  char usd[N][N], nusd[N][N];
  usd[0][0] = 1;
  for (int step = 0; step < k - 1; step++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (!usd[i][j])
          continue;
        for (int mask = 0; mask < MOD; mask++) {
          if (dp[i * N * MOD + j * MOD + mask] == -INFI) continue;
          for (int d = 0; d < 4; d++) {
            int dx = DD[d][0];
            int dy = DD[d][1];
            if (i + dx < 0 || j + dy < 0
            || i + dx >= n || j + dy >= m
            || f[i][j][mask][i + dx][j + dy] != a[i + dx][j + dy])
              continue;
            ndp[(i + dx) * N * MOD + (j + dy) * MOD + (mask * 4 + d) % MOD] = max(ndp[(i + dx) * N * MOD + (j + dy) * MOD + (mask * 4 + d) % MOD],
                                                                     dp[i * N * MOD + j * MOD + mask] + a[i + dx][j + dy]);
            nusd[i + dx][j + dy] = 1;
            if (step == k - 2)
              ans = max(ans, (ll)ndp[(i + dx) * N * MOD + (j + dy) * MOD + (mask * 4 + d) % MOD]);
          }
        }
      }
    }
    swap(dp, ndp);
    swap(nusd, usd);
    fill(ndp, ndp + N * N * MOD, -INFI);
    for (int j = 0; j < n; j++) {
      memset(nusd, 0, sizeof nusd);
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



//
// Created by watemus on 23.10.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
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

const int N = 301;

char f[N][N];
char *dps[N][N][N];
int dp[N][N][N];

void chmin(char *s, char *t) {
  int sl = strlen(s);
  int tl = strlen(t);
  for (int i = 0; i < tl; i++) {
    if (t[i] != '(' && t[i] != ')') {
      t[i] = '\0';
      tl = i;
      break;
    }
  }
  if (sl < tl || (sl == tl && strcmp(t, s) > 0)) {
    strcpy(s, t);
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  int sx = 0;
  int sy = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      memset(dp[i][j], -1, sizeof dp[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> f[i][j];
      if (f[i][j] == 'M') {
        sx = i;
        sy = j;
      }
    }
  }
  dp[sx][sy][0] = 0;
  dps[sx][sy][0] = new char[3];
  memset(dps[sx][sy][0], '\0', 3);
  char *ans = new char[N];
  memset(ans, '\0', sizeof ans);
  for (int x = sx; x > 1; x--) {
    for (int y = 1; y <= m; y++) {
      for (int bal = 0; bal < N; bal++) {
        if (dp[x][y][bal] == -1)
          continue;
        for (int dy = -1; dy <= 1; dy++) {
          if (y - dy == 0) continue;
          if (y - dy == m + 1) continue;
          int dbal = 0;
          char *nw = dps[x][y][bal];
          if (f[x - 1][y - dy] == '(') {
            nw[dp[x][y][bal]] = '(';
            dbal = 1;
          } else if (f[x - 1][y - dy] == ')') {
            dbal = -1;
            nw[dp[x][y][bal]] = ')';
          }
          if ((f[x - 1][y - dy] == '*' || x - 1 == 1) && bal + dbal == 0) {
            chmin(ans, nw);
          }
          if (bal + dbal >= 0) {
            if (f[x - 1][y - dy] != '*') {
              dp[x - 1][y - dy][bal + dbal] = max(dp[x - 1][y - dy][bal + dbal], dp[x][y][bal] + abs(dbal));
              if (dps[x - 1][y - dy][bal + dbal])
                chmin(dps[x - 1][y - dy][bal + dbal], nw);
              else {
                dps[x - 1][y - dy][bal + dbal] = new char[dp[x - 1][y - dy][bal + dbal] + 3];
                memset(dps[x - 1][y - dy][bal + dbal], '\0', dp[x - 1][y - dy][bal + dbal] + 3);
                strcpy(dps[x - 1][y - dy][bal + dbal], nw);
              }
            }
          }
          nw[dp[x][y][bal]] = '\0';
        }
        delete[] dps[x][y][bal];
      }
    }
  }
  cout << strlen(ans) << '\n';
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



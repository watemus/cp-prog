//
// Created by watemus on 13.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")

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

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 302;
int aa[N][N][N * 2];
int cur[N * 2], tcur[N * 2];

void run() {
  int n, m, s;
  cin >> n >> m >> s;
  vec<vec<char>> f(n + 2, vec<char>(m + 2, 'C'));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> f[i][j];
    }
  }
  ll ans = 0;
  // 1 ADD
  {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int way = 0;
        for (int k = i; k <= n; k++) {
          way += (f[k][j] == '#') + 1;
          aa[i][j][way]++;
        }
      }
    }
    for (int j = 1; j <= m; j++) {
      memset(cur, 0, sizeof cur);
      for (int i = 1; i <= n; i++) {
        for (int k = 0; k < 2 * N; k++) {
          cur[k] += aa[i][j][k];
        }
        if (f[i][j] == '.')
          memcpy(aa[i][j], cur, sizeof cur);
        else
          memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k < N * 2; k++) {
          aa[i][j][k] += aa[i][j][k - 1] + aa[i][j - 1][k] - aa[i][j - 1][k - 1];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j1 = 1; j1 <= m; j1++) {
        int cs = 0;
        for (int j2 = j1; j2 <= m; j2++) {
          cs += 1 + (f[i][j2] == '#');
          if (cs > s) break;
          ans += aa[i][j2][min(N * 2 - 1, s - cs + 1)] - aa[i][j1 - 1][min(N * 2 - 1, s - cs + 1)];
        }
      }
    }
  }
  // 1 DEL
  {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int way = 0;
        for (int k = i; k <= n; k++) {
          way += (f[k][j] == '#') + 1;
          aa[k][j][way]++;
        }
      }
    }
    for (int j = 1; j <= m; j++) {
      memset(cur, 0, sizeof cur);
      for (int i = 1; i <= n; i++) {
        memcpy(tcur, cur, sizeof cur);
        for (int k = 0; k < 2 * N; k++) {
          cur[k] += aa[i][j][k];
        }
        if (f[i][j] == '.')
          memcpy(aa[i][j], tcur, sizeof tcur);
        else
          memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k < N * 2; k++) {
          aa[i][j][k] += aa[i][j][k - 1] + aa[i][j - 1][k] - aa[i][j - 1][k - 1];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j1 = 1; j1 <= m; j1++) {
        int cs = 0;
        for (int j2 = j1; j2 <= m; j2++) {
          cs += 1 + (f[i][j2] == '#');
          if (cs > s) break;
          ans -= aa[i][j2][min(N * 2 - 1, s - cs + 1)] - aa[i][j1 - 1][min(N * 2 - 1, s - cs + 1)];
        }
      }
    }
  }
  // 2 ADD
  {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int way = 0;
        for (int k = i; k <= n; k++) {
          way += (f[k][j] == '#') + 1;
          aa[i][j][way]++;
        }
      }
    }
    for (int j = 1; j <= m; j++) {
      memset(cur, 0, sizeof cur);
      for (int i = 1; i <= n; i++) {
        for (int k = 0; k < 2 * N; k++) {
          cur[k] += aa[i][j][k];
        }
        if (f[i][j] == '#')
          memcpy(aa[i][j], cur, sizeof cur);
        else
          memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k < N * 2; k++) {
          aa[i][j][k] += aa[i][j][k - 1] + aa[i][j - 1][k] - aa[i][j - 1][k - 1];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j1 = 1; j1 <= m; j1++) {
        int cs = 0;
        for (int j2 = j1; j2 <= m; j2++) {
          cs += 1 + (f[i][j2] == '#');
          if (cs > s) break;
          ans += aa[i][j2][min(N * 2 - 1, s - cs + 2)] - aa[i][j1 - 1][min(N * 2 - 1, s - cs + 2)];
        }
      }
    }
  }
  // 2 DEL
  {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        memset(aa[i][j], 0, sizeof aa[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int way = 0;
        for (int k = i; k <= n; k++) {
          way += (f[k][j] == '#') + 1;
          aa[k][j][way]++;
        }
      }
    }
    for (int j = 1; j <= m; j++) {
        memset(cur, 0, sizeof cur);
        for (int i = 1; i <= n; i++) {
          memcpy(tcur, cur, sizeof cur);
          for (int k = 0; k < 2 * N; k++) {
            cur[k] += aa[i][j][k];
          }
          if (f[i][j] == '#')
            memcpy(aa[i][j], tcur, sizeof tcur);
          else
            memset(aa[i][j], 0, sizeof aa[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int k = 1; k < N * 2; k++) {
          aa[i][j][k] += aa[i][j][k - 1] + aa[i][j - 1][k] - aa[i][j - 1][k - 1];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j1 = 1; j1 <= m; j1++) {
        int cs = 0;
        for (int j2 = j1; j2 <= m; j2++) {
          cs += 1 + (f[i][j2] == '#');
          if (cs > s) break;
          ans -= aa[i][j2][min(N * 2 - 1, s - cs + 2)] - aa[i][j1 - 1][min(N * 2 - 1, s - cs + 2)];
        }
      }
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


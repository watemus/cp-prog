//
// Created by watemus on 13.10.2020.
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

void run() {
  int n, m, s;
  cin >> n >> m >> s;
  vec<vec<char>> f(n + 2, vec<char>(m + 2, 'C'));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> f[i][j];
    }
  }
  vec<vec<vec<int>>> bg(n + 2, vec<vec<int>>(m + 2, vec<int>(n * 2 + 10)));
  auto nd = bg;
  auto cnt1 = bg;
  auto cnt2 = bg;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int way = 0;
      for (int k = i; k <= n; k++) {
        way += (f[k][j] == '#') + 1;
        bg[i][j][way]++;
        nd[k][j][way]++;
      }
    }
  }
  for (int j = 1; j <= m; j++) {
    vec<int> cur(n * 2 + 10);
    for (int i = 1; i <= n; i++) {
      for (int k = 0; k < cur.size(); k++) {
        cur[k] += bg[i][j][k];
      }
      if (f[i][j] == '.')
        cnt1[i][j] = cur;
      else
        cnt2[i][j] = cur;
      /*
      for (int k = 0; k + 1 + (f[i][j] == '#') < cur.size(); k++) {
        cnt[i][j][k] = cnt[i][j][k + 1 + (f[i][j] == '#')];
      }
      for (int k = cur.size() - (1 + (f[i][j] == '#')); k  < cur.size(); k++) {
        cnt[i][j][k] = 0;
      }*/
      for (int k = 0; k < cur.size(); k++) {
        cur[k] -= nd[i][j][k];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k < n * 2 + 10; k++) {
        cnt1[i][j][k] += cnt1[i][j][k - 1] + cnt1[i][j - 1][k] - cnt1[i][j - 1][k - 1];
        cnt2[i][j][k] += cnt2[i][j][k - 1] + cnt2[i][j - 1][k] - cnt2[i][j - 1][k - 1];
      }
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j1 = 1; j1 <= m; j1++) {
      int cs = 0;
      for (int j2 = j1; j2 <= m; j2++) {
        cs += 1 + (f[i][j2] == '#');
        if (cs > s) break;
        ans += cnt1[i][j2][min(n * 2 + 9, s - cs + 1)] - cnt1[i][j1 - 1][min(n * 2 + 9, s - cs + 1)];
        ans += cnt2[i][j2][min(n * 2 + 9, s - cs + 2)] - cnt2[i][j1 - 1][min(n * 2 + 9, s - cs + 2)];
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

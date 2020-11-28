//
// Created by watemus on 29.10.2020.
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

const int N = 60;

int f[N][N];

inline void chg(int x, int y, int v) {
  if (x >= 0 && x < N && y >= 0 && y < N)
    f[x][y] = min(f[x][y], v);
}

void run() {
  int n;
  cin >> n;
  n *= 2;
  n++;
  {

    f[x][y] = 1;
    int cr = 2;
    int len = 2;
    x--;
    for (len = 2; len <= N * 2; len+=2) {
      if (c == 0) {
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          y++;
        }
        y--;
        x++;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          x++;
        }
        x--;
        y--;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          y--;
        }
        y++;
        x--;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          x--;
        }
      } else {
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          y--;
        }
        y++;
        x++;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          x++;
        }
        x--;
        y++;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          y++;
        }
        y--;
        x--;
        for (int i = 0; i < len; i++) {
          chg(x, y, cr);
          cr++;
          x--;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cout << f[i][j] << ' ';
    }
    cout << '\n';
  }
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



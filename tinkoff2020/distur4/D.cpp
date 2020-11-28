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

const int N = 3050;

int f[N][N], p[N][N];

inline void chg(int x, int y, int v) {
  if (x >= 0 && x < N && y >= 0 && y < N)
    f[x][y] = (v);
}

void run() {
  int n;
  cin >> n;
  if (n <= 1000) {
    int x = N / 2;
    int y = N / 2;
    int c = 0;
    f[x][y] = 1;
    int cr = 2;
    int len = 2;
    x--;
    for (len = 2; len <= N; len+=2) {
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
    for (int i = 1; i < N; i++) {
      for (int j = 1; j < N; j++) {
        p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + f[i][j];
      }
    }
    auto calc = [&](int x1, int y1, int x2, int y2) {
      x1 += N / 2;
      y1 += N / 2;
      x2 += N / 2;
      y2 += N / 2;
      return p[x2][y2] - p[x1 - 1][y2] - p[x2][y1 - 1] + p[x1 - 1][y1 - 1];
    };
    int q;
    cin >> q;
    while (q--) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << calc(-x2, y1, -x1, y2) % ll(1e9 + 7) << '\n';
    }
  } else {
    auto calc = [](int x, int y) -> int {
      if (pair<int, int>(x, y) == pair<int, int>(0, 0)) {
        return 1;
      }
      if (pair<int, int>(x, y) == pair<int, int>(1, 0)) {
        return 2;
      }
      if (pair<int, int>(x, y) == pair<int, int>(1, 1)) {
        return 3;
      }
      if (pair<int, int>(x, y) == pair<int, int>(0, 1)) {
        return 4;
      }
      if (pair<int, int>(x, y) == pair<int, int>(-1, 1)) {
        return 5;
      }
      if (pair<int, int>(x, y) == pair<int, int>(-1, 0)) {
        return 6;
      }
      if (pair<int, int>(x, y) == pair<int, int>(-1, -1)) {
        return 7;
      }
      if (pair<int, int>(x, y) == pair<int, int>(0, -1)) {
        return 8;
      }
      if (pair<int, int>(x, y) == pair<int, int>(1, -1)) {
        return 9;
      }
      int mx = max(abs(x), abs(y));
      int lw = (mx * 2 - 1) * (mx * 2 - 1) + 1;
      if (mx == x && y != -mx) {
        return y + mx + lw - 1;
      }
      lw += (mx * 2) - 1;
      if (mx == y) {
        return mx - x + lw;
      }
      lw += (mx * 2);
      if (mx == -x) {
        return mx - y + lw;
      }
      lw += (mx * 2);
      return x + mx + lw;
    };
    int t;
    cin >> t;
    while (t--) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << calc(x1, y1) % ll(1e9 + 7) << '\n';
    }
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



//
// Created by watemus on 18.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 5000;

char f[N][N];
int c[2];

void run() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    memset(f[i], 'a', sizeof f[i]);
  }
  int x;
  int y;
  cin >> x >> y;
  int step = 0;
  auto chg = [](int i, int j, char nval) {
    if (f[i][j] == '.') c[0]--;
    else if (f[i][j] == '#') c[1]--;
    if (nval == '.') c[0]++;
    else c[1]++;
    f[i][j] = nval;
  };
  while (x != -1 && y != -1) {
    char df = (step % 2 ? '.' : '#');
    char edf = (1 - step % 2 ? '.' : '#');
    x--, y--;
    chg(x, y, df);
    int tx = x - 1, ty = y;
    while (tx >= 0 && f[tx][y] != df) {
      tx--;
    }
    if (tx != -1) {
      tx = x - 1;
      while (tx >= 0 && f[tx][y] != df) {
        chg(tx, y, df);
        tx--;
      }
    }
    tx = x + 1, ty = y;
    while (tx < n && f[tx][y] != df) {
      tx++;
    }
    if (tx != n) {
      tx = x + 1;
      while (tx < n && f[tx][y] != df) {
        chg(tx, y, df);
        tx++;
      }
    }
    tx = x, ty = y - 1;
    while (ty >= 0 && f[x][ty] != df) {
      ty--;
    }
    if (ty != -1) {
      ty = y - 1;
      while (ty >= 0 && f[x][ty] != df) {
        chg(x, ty, df);
        ty--;
      }
    }
    tx = x, ty = y + 1;
    while (ty < m && f[x][ty] != df) {
      ty++;
    }
    if (ty != m) {
      ty = y + 1;
      while (ty < m && f[x][ty] != df) {
        chg(x, ty, df);
        ty++;
      }
    }
    step++;
    cout << c[1] - c[0] << endl;
    cin >> x >> y;
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



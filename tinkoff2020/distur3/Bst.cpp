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

#define int ll

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

void chmin(string &s, string &t) {
  if (s.size() < t.size() || (s.size() == t.size() && s > t)) {
    s = t;
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  int sy = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> f[i][j];
      if (f[i][j] == 'M') {
        sy = j;
      }
    }
  }
  string ans;
  int to = 1;
  for (int i = 0; i < n - 1; i++) {
    to *= 3;
  }
  for (int mask = 0; mask < to; mask++) {
    int cmask = mask;
    int y = sy;
    string cur;
    int bal = 0;
    for (int x = n - 1; x >= 1; x--) {
      if (cmask % 3 == 1) y--;
      if (cmask % 3 == 2) y++;
      if (y < 1 || y > m) {
        bal = -1;
        break;
      }
      cmask /= 3;
      if (f[x][y] == '(') {
        bal++;
        cur += '(';
      } else if (f[x][y] == ')') {
        bal--;
        if (bal < 0)
          break;
        cur += ')';
      } else if (f[x][y] == '*') {
        break;
      }
    }
    if (bal == 0) {
      chmin(ans, cur);
    }
  }
  cout << ans.size() << '\n';
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



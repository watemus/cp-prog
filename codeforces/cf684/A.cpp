//
// Created by watemus on 17.11.2020.
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

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> a(n, vec<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char ch;
      cin >> ch;
      a[i][j] = ch - '0';
    }
  }
  vec<tuple<int, int, int, int, int, int>> ans;
  auto apply = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
    a[x1][y1] = 1 - a[x1][y1];
    a[x2][y2] = 1 - a[x2][y2];
    a[x3][y3] = 1 - a[x3][y3];
    ans.emplace_back(x1 + 1, y1 + 1, x2 + 1, y2 + 1, x3 + 1, y3 + 1);
  };
  function<void(int, int)> make = [&](int x, int y) {
    if (a[x][y] == 1 && a[x][y + 1] == 0 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) {
      apply(x, y, x + 1, y, x, y + 1);
      make(x, y);
    } else if (a[x][y] == 0 && a[x][y + 1] == 1 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) {
      apply(x, y, x + 1, y + 1, x, y + 1);
      make(x, y);
    } else if (a[x][y] == 0 && a[x][y + 1] == 0 && a[x + 1][y] == 1 && a[x + 1][y + 1] == 0) {
      apply(x, y, x + 1, y + 1, x + 1, y);
      make(x, y);
    } else if (a[x][y] == 0 && a[x][y + 1] == 0 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 1) {
      apply(x, y + 1, x + 1, y + 1, x + 1, y);
      make(x, y);
    } else if (a[x][y] == 1 && a[x][y + 1] == 0 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 1) {
      apply(x, y, x + 1, y, x, y + 1);
      apply(x + 1, y + 1, x + 1, y, x, y + 1);
    } else if (a[x][y] == 0 && a[x][y + 1] == 1 && a[x + 1][y] == 1 && a[x + 1][y + 1] == 0) {
      apply(x, y, x + 1, y, x + 1, y + 1);
      apply(x, y, x, y + 1, x + 1, y + 1);
    } else if (a[x][y] == 1 && a[x][y + 1] == 1 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 0) {
      apply(x + 1, y, x, y, x + 1, y + 1);
      apply(x + 1, y + 1, x + 1, y, x, y + 1);
    } else if (a[x][y] == 1 && a[x][y + 1] == 0 && a[x + 1][y] == 1 && a[x + 1][y + 1] == 0) {
      apply(x, y + 1, x, y, x + 1, y + 1);
      apply(x + 1, y + 1, x + 1, y, x, y + 1);
    } else if (a[x][y] == 0 && a[x][y + 1] == 1 && a[x + 1][y] == 0 && a[x + 1][y + 1] == 1) {
      apply(x, y, x + 1, y, x, y + 1);
      apply(x + 1, y, x, y, x + 1, y + 1);
    } else if (a[x][y] == 0 && a[x][y + 1] == 0 && a[x + 1][y] == 1 && a[x + 1][y + 1] == 1) {
      apply(x, y, x + 1, y, x, y + 1);
      apply(x, y + 1, x, y, x + 1, y + 1);
    }
    vec<pair<int, int>> prs;
    for (int i = x; i <= x + 1; i++) {
      for (int j = y; j <= y + 1; j++) {
        if (a[i][j]) prs.push_back({i, j});
      }
    }
    if (prs.size() == 4) {
      apply(x, y, x + 1, y, x, y + 1);
      make(x, y);
    } else if (prs.size() == 3) {
      apply(prs[0].first, prs[0].second, prs[1].first, prs[1].second,prs[2].first, prs[2].second);
    }
  };
  for (int i = 0; i + 2 < n; i++) {
    for (int j = 0; j + 2 < m; j++) {
      if (a[i][j])
        apply(i, j, i + 1, j, i, j + 1);
    }
  }
  if (m % 2 && a[n - 2][0] && a[n - 1][0]) {
    apply(n - 2, 0, n - 1, 0, n - 1, 1);
  } else if (m % 2 && a[n - 2][0]) {
    apply(n - 2, 0, n - 2, 1, n - 1, 1);
  } else if (m % 2 && a[n - 1][0]) {
    apply(n - 1, 0, n - 1, 1, n - 2, 1);
  }
  if (n % 2 && a[0][m - 2] && a[0][m - 1]) {
    apply(0, m - 2, 0, m - 1, 1, m - 1);
  } else if (n % 2 && a[0][m - 2]) {
    apply(0, m - 2, 1, m - 2, 1, m - 1);
  } else if (n % 2 && a[0][m - 1]) {
    apply(0, m - 1, 1, m - 1, 1, m - 2);
  }
//    for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      cout << a[i][j];
//    }
//    cout << endl;
//  }
  for (int i = m % 2; i + 2 < m; i += 2) {
    make(n - 2, i);
  }
  for (int i = n % 2; i + 2 < n; i += 2) {
    make(i, m - 2);
  }
  make(n - 2, m - 2);
//  assert(ans.size() <= n * m);
  cout << ans.size() << '\n';
  for (auto [x1, y1, x2, y2, x3, y3] : ans) {
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x3 << ' ' << y3 << '\n';
  }
//  for (int i = 0; i < n; i++) {
//    for (int j = 0; j < m; j++) {
//      cout << a[i][j];
//    }
//    cout << endl;
//  }
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
   cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



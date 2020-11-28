//
// Created by watemus on 06.11.2020.
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

pair<vec<vec<int>>, int> solve(vec<vec<char>> &f) {
  vec<vec<int>> ans1, ans2;
  int need1, need2;
  {
    int n = f.size();
    int m = f[0].size();
    int need = 0;
    for (auto &row : f) {
      for (auto el : row) {
        need += (el == '*');
      }
    }
    int all = need;
    need = (need + 1) / 2;
    vec<vec<int>> ans(n, vec<int>(m, 2));
    for (int i = 0; i < n; i++) {
      need -= (f[i][0] == '*');
      ans[i][0] = 1;
    }
    if (n % 2 == 1) {
      for (int i = 1; i < m / 2; i++) {
        need -= (f[n / 2][i] == '*');
        ans[n / 2][i] = 1;
      }
    }
    vec<vec<int>> hv(n, vec<int>(m));
    vec<int> cans(n);
    for (int i = 0; i < n / 2; i++) {
      int cr = 0;
      for (int j = 1; j < m - 1; j++) {
        cr += (f[i][j] == '*');
      }
      hv[i][m - 2] = cr;
      for (int j = m - 3; j >= 0; j--) {
        cr -= (f[i][j + 1] == '*');
        cr += (f[n - i - 1][m - j - 2] == '*');
        hv[i][j] = cr;
      }
      int to = 0;
      for (int j = 1; j < m - 2; j++) {
        if (hv[i][j] < hv[i][to]) {
          to = j;
        }
      }
      cans[i] = to;
      need -= hv[i][to];
      for (int j = 1; j <= to; j++) {
        ans[i][j] = 1;
      }
      for (int j = 1; j < m - to - 1; j++) {
        ans[n - i - 1][j] = 1;
      }
    }
    for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < m - 1; j++) {
        if (hv[i][j] - hv[i][cans[i]] > 0 && hv[i][j] - hv[i][cans[i]] <= need) {
          need -= hv[i][j] - hv[i][cans[i]];
          cans[i] = j;
        }
      }
      for (int j = 0; j < m; j++) {
        if (j <= cans[i]) ans[i][j] = 1;
        else ans[i][j] = 2;
        if (j < m - cans[i] - 1) ans[n - i - 1][j] = 1;
        else ans[n - i - 1][j] = 2;
      }
    }
    ans1 = ans;
    need1 = abs(need);
  }
  {
    int n = f.size();
    int m = f[0].size();
    int need = 0;
    for (auto &row : f) {
      for (auto el : row) {
        need += (el == '*');
      }
    }
    int all = need;
    need = (need + 1) / 2;
    vec<vec<int>> ans(n, vec<int>(m, 2));
    for (int i = 0; i < n; i++) {
      need -= (f[i][0] == '*');
      ans[i][0] = 1;
    }
    if (n % 2 == 1) {
      for (int i = 1; i < m / 2; i++) {
        need -= (f[n / 2][i] == '*');
        ans[n / 2][i] = 1;
      }
    }
    vec<vec<int>> hv(n, vec<int>(m));
    vec<int> cans(n);
    for (int i = (n + 1) / 2; i < n; i++) {
      int cr = 0;
      for (int j = 1; j < m - 1; j++) {
        cr += (f[i][j] == '*');
      }
      hv[i][m - 2] = cr;
      for (int j = m - 3; j >= 0; j--) {
        cr -= (f[i][j + 1] == '*');
        cr += (f[n - i - 1][m - j - 2] == '*');
        hv[i][j] = cr;
      }
      int to = 0;
      for (int j = 1; j < m - 2; j++) {
        if (hv[i][j] < hv[i][to]) {
          to = j;
        }
      }
      cans[i] = to;
      need -= hv[i][to];
      for (int j = 1; j <= to; j++) {
        ans[i][j] = 1;
      }
      for (int j = 1; j < m - to - 1; j++) {
        ans[n - i - 1][j] = 1;
      }
    }
    for (int i = (n + 1) / 2; i < n; i++) {
      for (int j = 0; j < m - 1; j++) {
        if (hv[i][j] - hv[i][cans[i]] > 0 && hv[i][j] - hv[i][cans[i]] <= need) {
          need -= hv[i][j] - hv[i][cans[i]];
          cans[i] = j;
        }
      }
      for (int j = 0; j < m; j++) {
        if (j <= cans[i]) ans[i][j] = 1;
        else ans[i][j] = 2;
        if (j < m - cans[i] - 1) ans[n - i - 1][j] = 1;
        else ans[n - i - 1][j] = 2;
      }
    }
    ans2 = ans;
    need2 = abs(need);
  }
  if (need1 < need2)
    return {ans1, need1};
  else
    return {ans2, need2};
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<char>> f(n, vec<char>(m)), ff(m, vec<char>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> f[i][j];
      ff[j][i] = f[i][j];
    }
  }
  if (n == 1) {
    int all = 0;
    for (int i = 0; i < m; i++) {
      all += (f[0][i] == '*');
    }
    int have = (f[0][0] == '*');
    vec<int> ans(m, 2);
    ans[0] = 1;
    int i = 1;
    while (have < all / 2) {
      ans[i] = 1;
      have += (f[0][i] == '*');
      i++;
    }
    for (i = 0; i < m; i++) {
      cout << ans[i];
    }
    return;
  }
  auto s1 = solve(f);
  auto ans1 = s1.first;
  auto c1 = s1.second;
  auto s2 = solve(ff);
  auto ans2 = s2.first;
  auto c2 = s2.second;
  if (c1 <= c2) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << ans1[i][j];
      }
      cout << '\n';
    }
  } else {
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < m; i++) {
        cout << ans2[i][j];
      }
      cout << '\n';
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


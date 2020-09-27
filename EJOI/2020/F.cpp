//
// Created by watemus on 07.09.2020.
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
/*
template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}*/

#ifdef LOCAL
#else
#endif

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> cnt(n + 1, vec<int>(m + 1));
  vec<vec<set<pair<int, int>>>> g(n + 1, vec<set<pair<int, int>>>(m + 1));
  for (int i = 0; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char ch;
      cin >> ch;
      cnt[i][j] += (ch - '0');
      if (ch - '0')
        g[i][j].insert({1, 0});
      if (i + 1 <= n) {
        cnt[i + 1][j] += (ch - '0');
        if (ch - '0')
          g[i + 1][j].insert({-1, 0});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      char ch;
      cin >> ch;
      cnt[i][j] += (ch - '0');
      if (ch - '0')
        g[i][j].insert({0, 1});
      if (j + 1 <= m) {
        cnt[i][j + 1] += (ch - '0');
        if (ch - '0')
          g[i][j + 1].insert({0, -1});
      }
    }
  }
  vec<vec<int>> usd(n + 1, vec<int>(m + 1));
  int cntt = 0;
  function<void(int, int)> dfs = [&](int x, int y) {
    cntt++;
    usd[x][y]=1;
    for (auto dd : DD) {
      if (g[x][y].count(dd))
        continue;
      int nx = x + dd.first;
      int ny = y + dd.second;
      if (nx < 1 || nx > n)
        continue;
      if (ny < 1 || ny > m)
        continue;
      if (!usd[nx][ny]) {
        dfs(nx, ny);
      }
    }
  };
  vec<int> ans;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!usd[i][j] && cnt[i][j] == 2) {
        dfs(i, j);
        ans.push_back(cntt);
        cntt = 0;
      }
    }
  }
  sort(RALL(ans));
  if (ans.size() == 0) {
    cout << "0\n";
  }
  else if (ans.size() == 1) {
    cout << -ans[0] << "\n";
  } else {
    cout << ans[0] - ans[1] << '\n';
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



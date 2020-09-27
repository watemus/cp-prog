//
// Created by watemus on 08.09.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

void run() {
  int n;
  cin >> n;
  vec<int> h(n);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  vec<int> dp(n, INFL);
  multiset<int> smn, smx;
  vec<pair<int, int>> stmx, stmn;
  dp[n - 1] = 0;
  stmx.push_back({0, h.back()});
  stmn.push_back({0, h.back()});
  smn.insert(0);
  smx.insert(0);
  for (int i = n - 2; i >= 0; i--) {
    int xw = 0, nw = 0;
    while (stmx.size() && stmx.back().second <= h[i]) {
      if (stmx.back().second == h[i])
        xw = 1;
      dp[i] = min(dp[i], stmx.back().first + 1);
      smx.erase(stmx.back().first);
      stmx.pop_back();
    }
    if (stmx.size() && !xw) {
      dp[i] = min(dp[i], stmx.back().first + 1);
    }
    while (stmn.size() && stmn.back().second >= h[i]) {
      dp[i] = min(dp[i], stmn.back().first + 1);
      if (stmn.back().second == h[i]) {
        nw = 1;
      }
      smn.erase(stmn.back().first);
      stmn.pop_back();
    }
    if (stmn.size() && !nw) {
      dp[i] = min(dp[i], stmn.back().first + 1);
    }
    stmx.push_back({dp[i], h[i]});
    stmn.push_back({dp[i], h[i]});
  }
  cout << dp[0] << '\n';
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



//
// Created by watemus on 05.08.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
  int n;
  cin >> n;
  vec<pair<int, int>> segs(n);
  vec<int> coords;
  for (int i = 0; i < n; i++) {
    cin >> segs[i].first >> segs[i].second;
    coords.push_back(segs[i].first);
    coords.push_back(segs[i].second);
  }
  sort(ALL(coords));
  coords.resize(unique(ALL(coords)) - coords.begin());
  map<int, int> to;
  vec<vec<int>> dp(coords.size(), vec<int>(coords.size()));
  for (int i = 0; i < coords.size(); i++) {
    to[coords[i]] = i;
  }
  vec<vec<int>> segs_at(coords.size());
  for (auto &[l, r] : segs) {
    l = to[l], r = to[r];
    segs_at[l].push_back(r);
  }
  for (int i = coords.size() - 1; i >= 0; i--) {
    for (int j = i; j < coords.size(); j++) {
      if (j - i > 0) {
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
      }
      int cv = 0;
      for (int k : segs_at[i]) {
        if (k > j) continue;
        if (k == j) {
          cv++;
        } else {
          dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
      }
      dp[i][j] += cv;
    }
  }
  cout << dp[0].back() << '\n';
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



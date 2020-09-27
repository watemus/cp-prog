//
// Created by watemus on 21.08.2020.
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
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
  int x1, y1, z1, x2, y2,z2;
  cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
  int ans = 0, mn;
  mn = min(z1, y2);
  ans += 2 * mn;
  z1 -= mn;
  y2 -= mn;
  mn = min(y1, x2);
  y1 -= mn;
  x2 -= mn;
  mn = min(z1, x2);
  z1 -= mn;
  x2 -= mn;
  mn = min(z2, z1);
  z2 -= mn;
  z1 -= mn;
  mn = min(x1, z2);
  x1 -= mn;
  z2 -= mn;
  mn = min(x1, x2);
  x1 -= mn;
  x2 -= mn;
  mn = min(y1, y2);
  y1 -= mn;
  y2 -= mn;
  mn = min(x1, y2);
  x1 -= mn;
  y2 -= mn;
  mn = min(y1, z2);
  ans -= 2 * mn;
  z2 -= mn;
  y1 -= mn;
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



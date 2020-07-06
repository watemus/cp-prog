//
// Created by watemus on 01.07.2020.
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
  int n, k;
  cin >> n >> k;
  vec<vec<int>> a(n, vec<int>(n));
  int cnt = 0;
  for (int shift = 0; shift < n; shift++) {
    for (int i = 0; i < n; i++) {
      if (cnt < k) {
        a[i][(i + shift) % n] = 1;
        cnt++;
      }
    }
  }
  int rmin = INFI, rmax = 0, cmin = INFI, cmax = 0;
  for (int i = 0; i < n; i++) {
    int cur_r = 0;
    int cur_c = 0;
    for (int j = 0; j < n; j++) {
      cur_r += a[i][j];
      cur_c += a[j][i];
    }
    rmin = min(rmin, cur_r);
    rmax = max(rmax, cur_r);
    cmin = min(cmin, cur_c);
    cmax = max(cmax, cur_c);
  }
  cout << (rmax - rmin) * (rmax - rmin) + (cmax - cmin) * (cmax - cmin) << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << a[i][j];
    }
    cout << '\n';
  }
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t;
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


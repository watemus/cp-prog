//
// Created by watemus on 06.07.2020.
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

void run();

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


void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> a(n, vec<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i : {0, n - 1}) {
    for (int j : {0, m - 1}) {
      if (a[i][j] > 2) {
        cout << "NO\n";
        return;
      }
      a[i][j] = 2;
    }
  }
  for (int i = 1; i < n - 1; i++) {
    if (a[i][0] > 3) {
      cout << "NO\n";
      return;
    }
    if (a[i][m - 1] > 3) {
      cout << "NO\n";
      return;
    }
    a[i][0] = a[i][m - 1] = 3;
  }
  for (int i = 1; i < m - 1; i++) {
    if (a[0][i] > 3) {
      cout << "NO\n";
      return;
    }
    if (a[n - 1][i] > 3) {
      cout << "NO\n";
      return;
    }
    a[0][i] = a[n - 1][i] = 3;
  }
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      if (a[i][j] > 4) {
        cout << "NO\n";
        return;
      }
      a[i][j] = 4;
    }
  }
  cout << "YES\n";
  for (int i = 0; i <  n; i++) {
    for (int j = 0; j < m; j++) {
      cout << a[i][j] << ' ';
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



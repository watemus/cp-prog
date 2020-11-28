//
// Created by watemus on 11.11.2020.
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
  int c, p;
  cin >> c >> p;
  for (int i = 2; i <= min(n - 1, 10LL); i++) {
    for (int j = 2; j <= min(m - 1, 10LL); j++) {
      int c1 = max(i - 4, 0LL) * max(j - 4, 0LL);
      int c2 = max(n - 3 - i, 0LL) * max(j - 4, 0LL);
      int c3 = max(i - 4, 0LL) * max(m - 3 - j, 0LL);
      int c4 = max(n - 3 - i, 0LL) * max(m - 3 - j, 0LL);
//      cout << c1 + c2 + c3 + c4 << endl;
      if (c1 + c2 + c3 + c4 == p) {
        cout << i << ' ' << j << endl;
        return;
      }
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



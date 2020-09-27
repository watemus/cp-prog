//
// Created by watemus on 16.08.2020.
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
  int n;
  cin >> n;
  vec<vec<int>> a(n, vec<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i % 2 == 0) {
        a[i][j] = (1LL << (i + j));
      }
      cout << a[i][j] << ' ';
    }
    cout << endl;
  }
  int q;
  cin >> q;
  while (q--) {
    int have;
    cin >> have;
    int x = n - 1, y = n - 1;
    vec<pair<int, int>> ans;
    while (x != 0 || y != 0) {
      ans.emplace_back(x, y);
      if (x == 0) {
        y--;
        continue;
      }
      if (x % 2) {
        if (a[x - 1][y] & have) {
          x--;
        } else {
          y--;
        }
      } else {
        if (a[x][y - 1] & have) {
          y--;
        } else {
          x--;
        }
      }
    }
    ans.emplace_back(0, 0);
    reverse(ALL(ans));
    for (auto [cx, cy] : ans) {
      cout << cx + 1 << ' ' << cy + 1 << endl;
    }
  }
}

signed main() {
#ifdef LOCAL
  //std::freopen("input.txt", "r", stdin);
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



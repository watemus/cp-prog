//
// Created by watemus on 22.11.2020.
//

//
// Created by watemus on 22.11.2020.
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

const int N = 2e5;

void run() {
  int n, q;
  cin >> n >> q;
  vec<int> p(n), rp(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    rp[p[i] - 1] = i;
  }
  {
    int ans = 1;
    int cans = 1;
    for (int i = 1; i < n; i++) {
      if (rp[i] > rp[i - 1]) {
        cans += 1;
        ans = max(cans, ans);
      } else {
        cans = 1;
      }
    }
    cout << n - ans << '\n';
  }
  while (q--) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    swap(p[x], p[y]);
    rp[p[x] - 1] = x;
    rp[p[y] - 1] = y;
    int ans = 1;
    int cans = 1;
    for (int i = 1; i < n; i++) {
      if (rp[i] > rp[i - 1]) {
        cans += 1;
        ans = max(cans, ans);
      } else {
        cans = 1;
      }
    }
    cout << n - ans << '\n';
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



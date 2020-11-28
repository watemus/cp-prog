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


constexpr ld eps = 1e-15;
void run() {
  int n;
  cin >> n;
  vec<int> xs(n);
  for (int i = 0; i < n; i++) {
    cin >> xs[i];
  }
  ld w, v;
  cin >> w >> v;
  int q;
  cin >> q;
  cout << fixed << setprecision(20);
  while (q--) {
    int p, t, u;
    cin >> p >> t >> u;
    ld ans = t + ld(xs.back() - p) / ld(u);
    auto get = [&](ld T, ld s) {
      int l = -1;
      int r = INFI;
      while (l + 1 <r) {
        int mid = (l + r) / 2;
        if (mid * w + s / v >= T) {
          r = mid;
        } else {
          l = mid;
        }
      }
      return r;
    };
    ld cr = *lower_bound(ALL(xs), p);
    int gt = get(t + fabsl(cr - p) / u, cr);
    ans = min(ans, gt * w + ld(xs.back()) / v);
    cr = *prev(upper_bound(ALL(xs), p));
    gt = get(t + fabsl(cr - p) / u, cr);
    ans = min(ans, gt * w + ld(xs.back()) / v);
    cout << ans << '\n';
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



//
// Created by watemus on 30.09.2020.
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

const int MAXN = 1e6 + 10;

void run() {
  int n, m;
  cin >> n >> m;
  vec<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> a[i].FF >> a[i].SS;
  }
  vec<int> mx(MAXN * 2, -1);
  vec<int> xs(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    mx[x] = max(y, mx[x]);
    xs.push_back(x);
  }
  for (int i = MAXN - 2; i >= 0; i--) {
    mx[i] = max(mx[i], mx[i + 1]);
  }
  auto check = [&](int dx) {
    int ans = dx;
    int max_d = 0;
    for (auto [x, y] : a) {
      max_d = max(max_d, mx[x + dx] - y + 1);
    }
    return ans + max_d;
  };
  int ans = check(0);
  sort(ALL(xs));
  for (auto [x, y] : a) {
    auto x2 = lower_bound(ALL(xs), x);
    if (x2 != xs.end() ){
      if (*x2 >= x) {
        ans = min(ans, check(*x2 - x));
        ans = min(ans, check(*x2 - x + 1));
      }
    }
  }
  cout << ans << "\n";
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


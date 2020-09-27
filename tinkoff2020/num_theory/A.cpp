//
// Created by watemus on 26.09.2020.
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

int gcd(int a, int b, int *x, int *y) {
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }
  int nx, ny;
  int g = gcd(b, a % b, &nx, &ny);
  *x = ny;
  *y = nx - a / b * ny;
  return g;
}

void run() {
  int a, b, c;
  cin >> a >> b >> c;
  if (c % gcd(a, b) != 0) {
    cout << "Impossible\n";
    return;
  }
  int x, y;
  int g = gcd(a, b, &x, &y);
  x *= c / g;
  y *= c / g;
  if (x < 0) {
    int cnt = abs(x) / (b / g);
    x += cnt * (b / g);
    y -= cnt * (a / g);
    x += b / g;
    y -= a / g;
  }
  int cnt = x / (b / g);
  x -= (b / g) * cnt;
  y += (a / g) * cnt;
  cout << x << ' ' << y << '\n';
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



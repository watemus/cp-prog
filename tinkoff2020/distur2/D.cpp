//
// Created by watemus on 13.10.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr ld EPS = 1e-10;

void run() {
  int n;
  cin >> n;
  vec<pair<int, int>> rays(n);
  for (auto &ray : rays) {
    cin >> ray.first >> ray.second;
  }
  int pc, pd;
  pc = pd = 0;
  int m;
  cin >> m;
  bool was = true;
  cout << fixed << setprecision(20);
  for (int i = 0; i < m; i++) {
    int c, d;
    cin >> c >> d;
    if (!was) {
      c = (c ^ ((1LL << 29) - 1));
      d = (d ^ ((1LL << 29) - 1));
    }
    ld ans = -1;
    for (auto ray : rays) {
      ld a = ray.first;
      ld b = ray.second;
      ld cc = ld(c);
      ld dd = ld(d);
      ld cx = (dd - b) / (a - cc);
      if (cx > -EPS) {
        ans = max(cx, ans);
      }
    }
    if (ans < -EPS) {
      cout << "No cross\n";
      was = false;
    } else {
      cout << ans << '\n';
      was = true;
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



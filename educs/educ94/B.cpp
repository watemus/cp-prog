//
// Created by watemus on 25.08.2020.
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
  int p, f;
  cin >> p >> f;
  int c1, c2;
  cin >> c1 >> c2;
  int p1, p2;
  cin >> p1 >> p2;
  if (p1 > p2) {
    swap(p1, p2);
    swap(c1, c2);
  }
  int ans = 0;
  for (int i = 0; i <= c1; i++) {
    int sp = p - p1  * i;
    if (sp < 0) continue;
    int fr = min(f / p1, c1 - i);
    int sf = f - fr * p1;
    int o2 = sp / p2 + sf / p2;
    ans = max(ans, i + fr + min(o2, c2));
  }
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



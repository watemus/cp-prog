//
// Created by watemus on 19.11.2020.
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
  int bal1 = 0, bal2 = 0;
  int ans = 0;
  string s;
  cin >> s;
  int cnt1 = 0;
  int cnt2 = 0;
  for (auto el : s) {
    if (el == '[' || el == ']') {
      if (el == '[') {
        cnt1++;
      } else {
        if (cnt1 > 0)
          ans++;
        cnt1 = max(cnt1 - 1, 0LL);
      }
    } else {
      if (el == '(') {
        cnt2++;
      } else {
        if (cnt2 > 0)
          ans++;
        cnt2 = max(cnt2 - 1, 0LL);
      }
    }
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



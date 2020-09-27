//
// Created by watemus on 29.07.2020.
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
  int n, k;
  cin >> n >> k;
  int l1, r1, l2, r2;
  cin >> l1 >> r1 >> l2 >> r2;
  if (l1 > l2) {
    swap(l1, l2);
    swap(r1, r2);
  }
  int have = 0;
  have = max(0LL, min(r1, r2) - l2) * n;
  int ans = INFL;
  int steps = 0;
  for (int i = 0; i < n; i++) {
    if (have >= k) {
      ans = min(ans, steps);
      break;
    }
    steps += max(0LL, l2 - r1);
    int to_set = max(r2, r1) - l1 - max(0LL, min(r1, r2) - l2);
    steps += min(k - have, to_set);
    have += min(k - have, to_set);
    ans = min(ans, steps + (k - have) * 2);
  }
  cout << ans << '\n';
}жз
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



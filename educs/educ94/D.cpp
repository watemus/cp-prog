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
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vec<vec<int>> cnt_lt(n, vec<int>(n + 1)), cnt_rt(n, vec<int>(n + 1));
  cnt_lt[0][a[0]]++;
  for (int i = 1; i < n; i++) {
    cnt_lt[i] = cnt_lt[i - 1];
    cnt_lt[i][a[i]]++;
  }
  cnt_rt[n - 1][a[n - 1]]++;
  for (int i = n - 2; i >= 0; i--) {
    cnt_rt[i] = cnt_rt[i + 1];
    cnt_rt[i][a[i]]++;
  }
  int ans = 0;
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      int icnt = cnt_lt[i - 1][a[j]];
      int jcnt = cnt_rt[j + 1][a[i]];
      ans += icnt * jcnt;
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



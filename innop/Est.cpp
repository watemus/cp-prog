//
// Created by watemus on 22.11.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using namespace __gnu_pbds;

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
  int n;
  cin >> n;
  vec<pair<int, int>> a(n);
  cc_hash_table<int, int> cnt_col, cnt_row;
  cc_hash_table<int, int> cnt;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
    cnt_row[a[i].first]++;
    cnt_col[a[i].second]++;
    cnt[a[i].first * INFI + a[i].second]++;
  }
  int ans = 4;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i].first != a[j].first && a[i].second != a[j].second) {
        int cans = 0;
        if (cnt.find(a[i].first * INFI + a[j].second) == cnt.end()) {
          if (cnt_row[a[i].first] > 1 || cnt_col[a[j].second] > 1) {
            cans++;
          } else {
            cans += 2;
          }
        }
        if (cnt.find(a[j].first * INFI + a[i].second) == cnt.end()) {
          if (cnt_row[a[j].first] > 1 || cnt_col[a[i].second] > 1) {
            cans++;
          } else {
            cans += 2;
          }
        }
        ans = min(ans, cans);
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



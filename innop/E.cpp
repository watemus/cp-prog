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
  int ans = 4;
  int cnt_col2 = 0, cnt_row2 = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
    cnt_row[a[i].first]++;
    cnt_col[a[i].second]++;
    if (cnt_col[a[i].second] == 2) {
      ans = 3;
      cnt_col2++;
    }
    if (cnt_row[a[i].first] == 2) {
      ans = 3;
      cnt_row2++;
    }
    cnt[a[i].first * INFI + a[i].second]++;
  }
  if (cnt_row.size() == n && cnt_col.size() == 1 || cnt_row.size() == 1 && cnt_col.size() == n) {
    ans = 4;
  }
  if (cnt_col2 > 1 || cnt_row2 > 1) {
    ans = 2;
  }
  for (auto [x, y] : a) {
    int cr = cnt_row[x];
    int cc = cnt_col[y];
    if (cr > 1 && cc > 1 && n - cc - cr + 1 > 0) {
      ans = 2;
    }
  }
  cc_hash_table<int, vec<int>> cnt_rows, cnt_cols;
  for (auto [x, y] : a) {
    cnt_rows[x].push_back(cnt_col[y]);
    cnt_cols[y].push_back(cnt_row[x]);
  }
  for (auto &[x, v] : cnt_rows) {
    sort(RALL(v));
    if (v.size() > 1 && v[0] > 1 && v[1] > 1) {
      ans = 1;
    }
  }
  for (auto &[x, v] : cnt_cols) {
    sort(RALL(v));
    if (v.size() > 1 && v[0] > 1 && v[1] > 1) {
      ans = 1;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i].first != a[j].first && a[i].second != a[j].second) {
        int cans = 0;
        if (cnt.find(a[i].first * INFI + a[j].second) == cnt.end()) {
          cans = 5;
        }
        if (cnt.find(a[j].first * INFI + a[i].second) == cnt.end()) {
          cans = 5;
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



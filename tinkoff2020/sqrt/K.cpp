//
// Created by watemus on 15.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

#ifdef LOCAL
#else
#endif

const int mod = 1e9 + 7;
int pw[1010];

void run() {
  int n, k;
  cin >> n >> k;
  vec<int> a(n);
  pw[0] = 1;
  for (int i = 1; i < 1010; i++) {
    pw[i] = (pw[i - 1] * 2) % mod;
  }
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(ALL(a));
  int ans = 0;
  gp_hash_table<int, int> cnt;
  vec<pair<int, int>> to_add;
  for (int i = 0; i < n; i++) {
    to_add.clear();
    if (a[i] >= k) ans++;
    ans %= mod;
    for (auto [kk, v] : cnt) {
      if ((kk + a[i] - 1) / a[i] <= 1) {
        ans += v * pw[n - i - 1] % mod;
        ans %= mod;
      } else {
        to_add.emplace_back((kk + a[i] - 1) / a[i], v);
      }
    }
    to_add.emplace_back((k + a[i] - 1) / a[i], 1);
    for (auto [kk, v] : to_add) {
      cnt[kk] += v;
      cnt[kk] %= mod;
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



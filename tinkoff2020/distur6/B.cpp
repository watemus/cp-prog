//
// Created by watemus on 13.11.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <immintrin.h>
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

#define int __int128

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

const int N = 1 << 20;

void run() {
  map<int, int> to;
  ll n;
  cin >> n;
  if (n == 1) {
    cout << "2\n";
    return;
  }
  for (int i = 0; i < (1 << n); i++) {
    to[i] = rnd() * rnd();
  }
  int ans = 0;
  int cur = 0;
  map<int, int> cnt[4];
  cnt[0][0] = 1;
  for (int i = 1; i <= (1 << n); i++) {
    ll el;
    cin >> el;
    el = min(el, (1 << n) - el - 1);
    cur ^= to[el];
    ans += cnt[i % 4][cur];
    cnt[i % 4][cur]++;
  }
  int m = (1 << n);
  cout << ll((m * (m + 1)) / 2 - ans) << '\n';
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



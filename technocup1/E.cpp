//
// Created by watemus on 25.10.2020.
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

#define int __int128

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'069;
constexpr int INFI = 1'000'000'069;
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

ll a, b, c, d;

int check(int m) {
  int k = (d * m - c) / d;
  int hp = a * (m / d);
  hp -= (k * (k + 1)) / 2 * b * d;
  hp -= (m / d - k) * c * b;
  return hp;
}

void run() {
  cin >> a >> b >> c >> d;
  int l = 0;
  int r = 1000;
  while (l + 100 < r) {
    int m1 = (l + r) / 3;
    int m2 = (l + r) * 2 / 3;
    if (check(m1 * d) < check(m2 * d)) {
      l = m1;
    } else {
      r = m2;
    }
  }
  int ans = 0;
  for (; l <= r; l++) {
    ans = max(ans, check(l));
  }
  if (ans == INFL) {
    cout << "-1\n";
  } else {
    cout << (ll)ans << '\n';
  }
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  ll t = 1;
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



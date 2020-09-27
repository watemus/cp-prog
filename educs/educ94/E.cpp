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

//#define int ll

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
  function<int(int, int, int)> calc = [&](int lb, int rb, int h) {
    if (rb < lb)
      return 0;
    int ans = rb - lb + 1;
    int mn = INFI;
    for (int i = lb; i <= rb; i++) {
      if (a[i] < mn) mn = a[i];
    }
    int cans = (mn - h);
    int prv = lb - 1;
    for (int i = lb; i <= rb + 1; i++) {
      if (i == rb + 1 || a[i] == mn) {
        cans += calc(prv + 1, i - 1, mn);
        prv = i;
      }
    }
    return min(ans, cans);
  };
  cout << calc(0, n - 1, 0) << '\n';
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



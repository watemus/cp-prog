//
// Created by watemus on 09.10.2020.
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

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run(int n, int m) {
  vec<int> a(n);
  for (int i = 0; i < m; i++) {
    char q;
    cin >> q;
    if (q == '^') {
      int lq, rq, x;
      cin >> lq >> rq >> x;
      for (int j = lq - 1; j < rq; j++) {
        a[j] = max(a[j], x);
      }
    } else {
      int lq, rq;
      cin >> lq >> rq;
      lq--;
      int sm = 0;
      for (int j = lq; j < rq; j++) {
        sm += a[j];
      }
      int b = rq - lq;
      int g = gcd(sm, b);
      sm /= g;
      b /= g;
      cout << sm;
      if (b != 1) {
        cout << '/' << b;
      }
      cout << "\n";
    }
  }
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
  // cout << fixed << setprecision(20);
  while (t--) {
    int n, m;
    while (true) {
      cin >> n >> m;
      if (n == 0 && m == 0)
        return 0;
      run(n, m);
    }
  }
  return 0;
}

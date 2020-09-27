//
// Created by watemus on 27.09.2020.
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

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

void run() {
  int n, m;
  cin >> n >> m;
  vec<int> primes;
  for (int i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      primes.push_back(i);
      while (m % i == 0) {
        m /= i;
      }
    }
  }
  if (m > 1) {
    primes.push_back(m);
  }
  int ans = n;
  for (int mask = 1; mask < (1 << primes.size()); mask++) {
    int p = 1;
    int cnt = 0;
    for (int i = 0; i < primes.size(); i++) {
      if ((1 << i) & mask) {
        cnt++;
        p *= primes[i];
      }
    }
    if (cnt % 2) {
      ans -= n / p;
    } else {
      ans += n / p;
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



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
  string s;
  cin >> s;
  int n = s.size();
  vec<int> suff_o(n, INFI), pref_z(n, -INFI);
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      pref_z[i] = pref_z[i - 1];
    }
    if (s[i] == '0') {
      pref_z[i] = i;
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    if (i < n - 1) {
      suff_o[i] = suff_o[i + 1];
    }
    if (s[i] == '1') {
      suff_o[i] = i;
    }
  }
  auto check = [&](int k) -> tuple<int, int, int> {
    tuple<int, int, int> ans = {-1, 0, k};
    int z = 0;
    int o = k;
    for (int i = 0; i < n; i += k) {
      int az = pref_z[min(n - 1, i + k - 1)] - i;
      int ao = suff_o[i] - i;
      z = max(z, az);
      o = min(o, ao);
    }
    if (z < o) {
      get<0>(ans) = (k - z - 1) * (n / k) + max(0LL, n % k - z - 1);
      get<1>(ans) = z;
    }
    return ans;
  };
  tuple<int, int, int> ans = {-1, -1, -1};
  for (int i = 1; i <= n; i++) {
    ans = max(ans, check(i));
  }
  if (get<0>(ans) == -1) {
    cout << -1 << '\n';
  } else {
    for (int i = 0; i < n; i++) {
      if (i % get<2>(ans) <= get<1>(ans)) {
        cout << 0;
      } else {
        cout << 1;
      }
    }
    cout << '\n';
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
//   cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



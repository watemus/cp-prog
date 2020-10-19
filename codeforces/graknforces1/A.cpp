//
// Created by watemus on 30.09.2020.
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
  int n;
  cin >> n;
  vec<int> a(n), b(n), c(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  for (int i = 0; i < n; i++) {
    cin >> c[i];
  }
  vec<int> ans(n);
  ans[0] = a[0];
  for (int i = 1; i < n - 1; i++) {
    if (b[i] != ans[i - 1]) {
      ans[i] = b[i];
    }
    if (a[i] != ans[i - 1]) {
      ans[i] = a[i];
    }
    if (c[i] != ans[i - 1]) {
      ans[i] = c[i];
    }
  }
  if (b[n - 1] != ans[n - 1 - 1] && b[n - 1] != ans[0]) {
    ans[n - 1] = b[n - 1];
  }
  if (a[n - 1] != ans[n - 1 - 1] && a[n - 1] != ans[0]) {
    ans[n - 1] = a[n - 1];
  }
  if (c[n - 1] != ans[n - 1 - 1] && c[n - 1] != ans[0]) {
    ans[n - 1] = c[n - 1];
  }
  for (int i = 00; i < n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
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



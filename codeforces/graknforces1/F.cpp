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

vec<pair<int, int>> ans;

void rec(int l, int r) {
  if (l + 1 == r) {
    ans.push_back({l, r});
  } else {
    int mid = (l + r) / 2;
    rec(l, mid);
    rec(mid + 1, r);
    int d = mid + 1 - l;
    for (int i = l; i <= mid; i++) {
      ans.emplace_back(i, i + d);
    }
  }
}

void run() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << "0\n";
    return;
  }
  int mx = 1;
  while (mx <= n) {
    mx *= 2;
  }
  mx /= 2;
  rec(1, mx);
  for (int i = 2; i <= mx; i++) {
    ans.emplace_back(n - i + 1, n);
  }
  rec(n - mx + 1, n);
  cout << ans.size() << '\n';
  for (auto [i, j] : ans) {
    cout << i << ' ' << j << "\n";
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
  while (t--) {
    run();
  }
  return 0;
}



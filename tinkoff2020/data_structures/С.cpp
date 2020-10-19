//
// Created by watemus on 03.10.2020.
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

const int N = 1 << 17;

int a[N + 228];
vec<int> t[2 * N + 228];

void build() {
  for (int i = 0; i < N; i++) {
    t[i + N].push_back(a[i]);
  }
  for (int i = N - 1; i > 0; i--) {
    merge(ALL(t[i * 2]), ALL(t[i * 2 + 1]), back_inserter(t[i]));
  }
}

int get(int l, int r, int x, int y) {
  l += N;
  r += N;
  int ans = 0;
  while (l < r) {
    if (l & 1) {
      ans += upper_bound(ALL(t[l]), y) - lower_bound(ALL(t[l]), x);
      l++;
    }
    if (r & 1) {
      r--;
      ans += upper_bound(ALL(t[r]), y) - lower_bound(ALL(t[r]), x);
    }
    l /= 2;
    r /= 2;
  }
  return ans;
}

void run() {
  int n, m;
  cin >> n >> m;
  memset(a, -1, sizeof a);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  build();
  for (int i = 0; i < m; i++) {
    int l, r, x, y;
    cin >> l >> r >> x >> y;
    l--;
    cout << get(l, r, x, y) << '\n';
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



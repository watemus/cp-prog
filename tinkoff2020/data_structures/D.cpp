//
// Created by watemus on 06.10.2020.
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

const int N = 1 << 18;

int a[N + 228];
vec<int> t[N * 2 + 228];
vec<int> p[N * 2 + 228];

void build() {
  for (int i = 0; i < N; i++) {
    t[i + N] = {a[i]};
    p[i + N] = {0, a[i]};
  }
  for (int i = N; i > 0; i--) {
    merge(ALL(t[i * 2]), ALL(t[i * 2 + 1]), back_inserter(t[i]));
    p[i].resize(t[i].size() + 1);
    for (int j = 1; j < p[i].size(); j++) {
      p[i][j] = p[i][j - 1] + t[i][j - 1];
    }
  }
}

int get(int l, int r, int x) {
  l += N;
  r += N;
  int ans = 0;
  while (l < r) {
    if (l & 1) {
      ans += p[l][upper_bound(ALL(t[l]), x) - t[l].begin()];
      l++;
    }
    if (r & 1) {
      r--;
      ans += p[r][upper_bound(ALL(t[r]), x) - t[r].begin()];
    }
    l /= 2;
    r /= 2;
  }
  return ans;
}

void run() {
  int n;
  cin >> n;
  fill(a, a + N + 228, INFI);
  int m;
  cin >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  build();
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--;
    int prv = 0;
    int cur = get(l, r, prv + 1);
    while (cur != prv) {
      prv = cur;
      cur = get(l, r, prv + 1);
    }
    cout << prv + 1 << '\n';
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



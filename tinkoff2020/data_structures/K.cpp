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

const int N = 2e5 + 10;
const int LOGN = 18;

int t[N];

void modify(int at, int val) {
  for (int i = at; i < N; i += (i & -i)) {
    t[i] += val;
  }
}

int get(int at) {
  int ans = 0;
  for (int i = at; i > 0; i -= (i & -i)) {
    ans += t[i];
  }
  return ans;
}

int find_kth(int l, int r, int k) {
  k += get(l - 1);
  int at = 0;
  for (int i = LOGN; i >= 0; i--) {
    if (at + (1 << i) < N && t[at + (1 << i)] < k) {
      at += (1 << i);
      k -= t[at];
    }
  }
  if (at >= r)
    return -1;
  return at + 1;
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    int el;
    cin >> el;
    modify(i, el == 0);
    a[i] = el == 0;
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    char q;
    cin >> q;
    if (q == 'u') {
      int at, val;
      cin >> at >> val;
      modify(at, -a[at]);
      a[at] = val == 0;
      modify(at, a[at]);
    } else {
      int l, r, k;
      cin >> l >> r >> k;
      cout << find_kth(l, r, k) << '\n';
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
  while (t--) {
    run();
  }
  return 0;
}



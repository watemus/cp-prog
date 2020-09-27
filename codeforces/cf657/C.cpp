//
// Created by watemus on 03.08.2020.
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
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
  int n, m;
  cin >> n >> m;
  vec<pair<int, int>> a(m), b(m), ab(m);
  for (int i = 0; i < m; i++) {
    cin >> a[i].first >> b[i].first;
    ab[i] = {a[i].first, b[i].first};
    a[i].second = b[i].second = i;
  }
  sort(ALL(a));
  int mxb = 0;
  int sma = 0;
  int ans = 0;
  for (int i = m - 1; i >= 0; i--) {
    int have = m - i;
    b[a[i].second].second = i;
    if (have > n) continue;
    sma += ab[a[i].second].first;
    mxb = max(mxb, ab[a[i].second].second);
    ans = max(ans, sma + mxb * (n - have));
  }
  vec<int> suf_a(m);
  suf_a.back() = a.back().first;
  for (int i = m - 2; i >= 0; i--) {
    suf_a[i] = suf_a[i + 1] + a[i].first;
  }
  for (int i = 0; i < m; i++) {
    int at = upper_bound(ALL(a), pair{b[i].first, -1LL}) - a.begin();
    int rem = n - 1;
    if (m - at > rem) {
      at = m - rem;
    }
    int cans = (at < m ? suf_a[at] : 0);
    int tm = n - (m - at);
    if (b[i].second < at) {
      cans += a[b[i].second].first;
      tm--;
    }
    cans += b[i].first * tm;
    ans = max(ans, cans);
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



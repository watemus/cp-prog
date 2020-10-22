//
// Created by watemus on 19.10.2020.
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

const int N = 2e5 + 10;
const int LOG_N = 19;

int n;

int dp[N];
int cnt[N];
int a[N];

void calc(int Y) {
  vec<pair<int, pair<int, int>>> segs;
  dp[0] = cnt[0] = 0;
  for (int i = 1; i <= n + 1; i++) {
    dp[i] = 0;
    cnt[i] = 0;
    segs.emplace_back(a[i], pair{dp[i - 1], cnt[i - 1]});
    for (int j = (int)segs.size() - 2; j >= 0; j--) {
      segs[j].first |= a[i];
    }
    sort(ALL(segs));
    vec<pair<int, pair<int, int>>> new_segs = {segs[0]};
    for (int j = 1; j < segs.size(); j++) {
      if (new_segs.back().first == segs[j].first) {
        new_segs.back().second = max(new_segs.back().second, segs[j].second);
      } else {
        new_segs.push_back(segs[j]);
      }
    }
    segs = new_segs;
    for (auto [_or, vals] : segs) {
      if (pair(vals.first + _or + Y, vals.second + 1) > pair(dp[i], cnt[i])) {
        dp[i] = vals.first + _or + Y;
        cnt[i] = vals.second + 1;
      }
    }
  }
}

int rd() {
  ll el;
  cin >> el;
  return el;
}

int k;

void run() {
  n = rd();
  k = rd();
  int tt = 0;
  for (int i = 1; i <= n; i++) {
    a[i] = rd();
  }
  int l = -INFL;
  int r = INFL;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    calc(mid);
    if (cnt[n] < k) {
      l = mid;
    } else {
      r = mid;
    }
  }
  calc(r);
  cout << ll(dp[n] - r * k) << '\n';
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



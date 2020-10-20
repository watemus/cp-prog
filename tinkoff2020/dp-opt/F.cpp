//
// Created by watemus on 20.10.2020.
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

const int N = 1e5 + 10;
const int K = 22;

int cnt[N], a[N], p[N];
int dp[K][N];
int opt[K][N];

int lc = 1, rc = 1;
int cost = 0;
inline int get(int l, int r) {
  while (rc < r) {
    rc++;
    cost -= cnt[a[rc]] * (cnt[a[rc]] - 1) / 2;
    cnt[a[rc]]++;
    cost += cnt[a[rc]] * (cnt[a[rc]] - 1) / 2;
  }
  while (lc > l) {
    lc--;
    cost -= cnt[a[lc]] * (cnt[a[lc]] - 1) / 2;
    cnt[a[lc]]++;
    cost += cnt[a[lc]] * (cnt[a[lc]] - 1) / 2;
  }
  while (rc > r) {
    cost -= cnt[a[rc]] * (cnt[a[rc]] - 1) / 2;
    cnt[a[rc]]--;
    cost += cnt[a[rc]] * (cnt[a[rc]] - 1) / 2;
    rc--;
  }
  while (lc < l) {
    cost -= cnt[a[lc]] * (cnt[a[lc]] - 1) / 2;
    cnt[a[lc]]--;
    cost += cnt[a[lc]] * (cnt[a[lc]] - 1) / 2;
    lc++;
  }
  return cost;
}

void calc(int k, int l, int r, int opt_l, int opt_r) {
  if (l > r)
    return;
  int mid = (l + r) / 2;
  dp[k][mid] = INFL;
  for (int i = max(k - 1, opt_l); i <= min(mid - 1, opt_r); i++) {
    int cur_dp = dp[k - 1][i] + get(i + 1, mid);
    if (cur_dp < dp[k][mid]) {
      dp[k][mid] = cur_dp;
      opt[k][mid] = i;
    }
  }
  calc(k, l, mid - 1, opt_l, opt[k][mid]);
  calc(k, mid + 1, r, opt[k][mid], opt_r);
}

void run() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cnt[a[1]] = 1;
  for (int i = 1; i <= n; i++) {
    dp[1][i] = get(1, i);
    opt[1][i] = 0;
  }
  for (int i = 2; i <= k; i++) {
    calc(i, i, n, 1, n + 1);
  }
  cout << dp[k][n] << '\n';
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



//
// Created by watemus on 18.10.2020.
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

const int N = 2002;

int dp[N][N];
int opt[N][N];
string ans[N];

void make_ans(int l, int r) {
  if (r == l)
    return;
  for (int i = l; i <= opt[l][r]; i++) {
    ans[i].push_back('0');
  }
  for (int j = opt[l][r] + 1; j <= r; j++) {
    ans[j].push_back('1');
  }
  make_ans(l, opt[l][r]);
  make_ans(opt[l][r] + 1, r);
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n + 1), pa(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pa[i] = pa[i - 1] + a[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) {
        dp[i][i] = a[i];
        opt[i][i] = i;
      } else {
        dp[i][j] = INFL;
      }
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = opt[i][j - 1]; k <= min(opt[i + 1][j], j - 1); k++) {
        int cur_val = dp[i][k] + dp[k + 1][j] + pa[j] - pa[i - 1];
        if (cur_val < dp[i][j]) {
          opt[i][j] = k;
          dp[i][j] = cur_val;
        }
      }
    }
  }
  make_ans(1, n);
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
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



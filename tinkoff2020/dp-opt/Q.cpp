//
// Created by watemus on 21.10.2020.
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

constexpr int DIGITS = 20;
constexpr int MAXN = 50;

int dp[DIGITS][MAXN];
int sm[MAXN];

void run() {
  for (int d = 1; d <= 9; d++) {
    dp[d][1] = 1;
  }
  sm[1] = 9;
  for (int i = 2; i < MAXN; i++) {
    sm[i] = sm[i - 1];
    for (int cd = 1; cd <= 9; cd++) {
      dp[cd][i] = 0;
      for (int kd = cd; kd <= 9; kd++) {
        dp[cd][i] += dp[kd][i - 1];
      }
      sm[i] += dp[cd][i];
    }
  }
  sm[0] = 0;
  int lst = 0;
  int n;
  cin >> n;
  while (sm[lst] < n)
    lst++;
  n -= sm[lst - 1];
  int cr = 1;
  while (lst > 0) {
    int csm = 0;
    while (csm + dp[cr][lst] < n) {
      csm += dp[cr][lst];
      cr++;
    }
    n -= csm;
    cout << cr;
    lst--;
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



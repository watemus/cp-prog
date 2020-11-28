//
// Created by watemus on 12.11.2020.
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

//#define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1000000000000000069;
constexpr int INFI = 1000000069;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(69);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 1e5 + 10;
const int K = 1010;

unsigned short dp[N][K];

void run() {
  string s(1e5, 'a');
  int k;
  cin >> k;
  for (int i = 3; i < s.size(); i++) {
    int cr = int(s[i - 3] != 'B') + int(s[i - 2] != 'E') + int(s[i - 1] != 'E') + int(s[i] != 'F');
    for (int j = cr; j <= k; j++) {
      dp[i + 1][j] = max((int)dp[i][j], dp[i - 3][j - cr] + 1);
    }
  }
  int ans = 0;
  for (int i = 0; i <= k; i++) {
    ans = max((int)dp[s.size()][i], ans);
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



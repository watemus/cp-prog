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

const int N = 1 << 21;

int k[N * 2 + 10];
int b[N * 2 + 10];
struct Li_Chao {
  Li_Chao() {
    fill(b, b + N * 2 + 10, INFL);
    memset(k, 0, sizeof k);
  }

  void add_line(int k1, int b1) {
    int v = 1;
    int l = 0;
    int r = N;
    while (true) {
      int mid = (l + r) / 2;
      int xc = k[v] * mid + b[v];
      int xn = k1 * mid + b1;
      bool mid_cond = xc >= xn;
      xc = k[v] * l + b[v];
      xn = k1 * l + b1;
      bool l_cond = xc >= xn;
      if (mid_cond) {
        swap(k[v], k1);
        swap(b[v], b1);
      }
      if (r - l == 1)
        break;
      if (l_cond != mid_cond) {
        r = mid;
        v = v * 2;
      } else {
        l = mid;
        v = v * 2 + 1;
      }
    }
  }

  int get(int x) {
    int v = x + N;
    int ans = INFL;
    while (v > 0) {
      ans = min(ans, k[v] * x + b[v]);
      v /= 2;
    }
    return ans;
  }
};

void run() {
  int n;
  cin >> n;
  vec<pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  sort(ALL(a));
  vec<pair<int, int>> na;
  for (int i = 0; i < n; i++) {
    while (na.size() && a[i].first >= na.back().first && a[i].second >= na.back().second) {
      na.pop_back();
    }
    na.push_back(a[i]);
  }
  a = na;
  vec<int> dp(n);
  dp[0] = a[0].first * a[0].second;
  Li_Chao t;
  t.add_line(a[0].second, 0);
  for (int i = 1; i < a.size(); i++) {
    t.add_line(a[i].second, dp[i - 1]);
    dp[i] = t.get(a[i].first);
  }
  cout << dp[a.size() - 1] << '\n';
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



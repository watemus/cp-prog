//
// Created by watemus on 04.12.2020.
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

const int N = 1e6 + 10;

int cnt[N];
int to[N];
vec<bool> sts[N];

void run() {
  int n, k;
  cin >> n >> k;
  int logn = 0;
  int tn = n;
  while (tn > 0) {
    logn++;
    tn /= 2;
  }
  logn++;
  for (int i = 0; i < min(logn, k); i++) {
    sts[i].resize(n);
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int el;
      cin >> el;
      sts[i][el - 1] = true;
    }
  }
  {
    for (int i = 0; i < min(logn, k); i++) {
      for (int j = 1; j <= n; j++) {
        if (sts[i][j - 1]) {
        } else {
          to[j] += (1 << i);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      cnt[to[i]]++;
    }
    string ans;
    int ansik = INFI;
    for (int mask = 0; mask < (1 << min(k, logn)); mask++) {
      if (cnt[mask] < ansik) {
        ansik = cnt[mask];
        ans = string(min(k, logn), '1');
        for (int j = 0; j < min(k, logn); j++) {
          if (mask & (1 << j)) {
            ans[j] = '0';
          }
        }
      }
    }
    cout << ans;
    for (int i = min(k, logn); i < k; i++) {
      cout << 0;
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



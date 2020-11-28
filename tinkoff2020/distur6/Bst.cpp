//
// Created by watemus on 13.11.2020.
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

void run() {
  int m;
  cin >> m;
  if (m == 1) {
    cout << "2\n";
    return;
  }
  int n = (1 << m);
  vec<int> pos(n), a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    pos[a[i]] = i;
  }
  vec<int> to(n);
  for (int i = 0; i < n; i++) {
    to[i] = pos[n - a[i] - 1];
  }
  int ans = n * (n + 1) / 2;
  for (int i = 0; i < n; i++) {
    int mn = to[i];
    int mx = to[i];
    for (int j = i; j < n; j++) {
      mn = min(mn, to[j]);
      mx = max(to[j], mx);
      if (mn < i) break;
      if (mn == i && mx == j && (j - i + 1) % 4 == 0) {
        ans--;
      }
    }
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


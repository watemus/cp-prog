//
// Created by watemus on 23.08.2020.
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
  int n, m, d, q;
  cin >> n >> m >> d >> q;
  vec<tuple<int, int, int>> edges(m);
  for (auto &[u, v, c] : edges) {
    cin >> u >> v >> c;
    u--, v--;
  }
  vec<int> cl(n);
  for (int i = 0; i < n; i++)
    cin >> cl[i];
  for (int i = 0; i < q; i++) {
    int u, c;
    cin >> u >> c;
    u--;
    cl[u] = c;
    int ans = INFI;
    for (auto [a, b, c] : edges) {
      if (cl[a] != cl[b]) {
        ans = min(ans, c);
      }
    }
    cout << ans << '\n';
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



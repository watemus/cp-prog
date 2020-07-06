//
// Created by watemus on 06.07.2020.
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

void run();

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


void run() {
  int n;
  cin >> n;
  vec<vec<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vec<int> clr(n);
  int cnt_clr[2] = {0, 0};
  function<void(int, int, int)> dfs = [&](int v, int p, int dep) {
    cnt_clr[dep % 2]++;
    for (int u : g[v]) {
      if (u != p) {
        dfs(u, v, dep + 1);
      }
    }
  };
  dfs(0, 0, 0);
  cout << min(cnt_clr[0], cnt_clr[1]) - 1 << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/



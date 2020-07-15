//
// Created by watemus on 12.07.2020.
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
  //std::freopen("input.txt", "r", stdin);
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
  auto ask = [&](int lb, int rb) {
    cout << "? " << lb << ' ' << rb << endl;
    int x, f;
    cin >> x >> f;
    return pair(x, f);
  };
  map<int, int> len;
  vec<int> ans(n + 1);
  function<int(int, int)> solve = [&](int lb, int rb) {
    if (lb > rb) return lb - 1;
    auto [x, f] = ask(lb, rb);
    if (len.count(x)) {
      int start = rb - f + 1;
      int end = start + len[x] - 1;
      for (int i = start; i <= end; i++) {
        ans[i] = x;
      }
      len.erase(x);
      solve(lb, rb - f);
      return end;
    } else {
      len[x] = f;
      int lc = lb;
      int rc = lb + f - 1;
      while (len.count(x)) {
        lc = solve(lc, rc) + 1;
        rc = lc + f - 1;
      }
      return solve(lc, rb);
    }
  };
  solve(1, n);
  cout << "! ";
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/



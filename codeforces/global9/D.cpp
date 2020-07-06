//
// Created by watemus on 04.07.2020.
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

void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  set<int> unused;
  for (int i = 0; i < n; i++) unused.insert(i);
  auto mex = [&]() {
    set<int> st;
    for (int i = 0; i < n; i++) {
      st.insert(a[i]);
    }
    for (int i = 0; i <= n; i++) {
      if (!st.count(i)) return i;
    }
    return n;
  };
  vec<int> ans;
  while (unused.size()) {
    int mx = mex();
    if (mx == n) {
      int idx = *unused.begin();
      ans.push_back(idx + 1);
      a[idx] = mx;
    } else {
      unused.erase(mx);
      ans.push_back(mx + 1);
      a[mx] = mx;
    }
  }
  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i << ' ';
  }
  cout << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


//
// Created by watemus on 19.11.2020.
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
  int n, m;
  cin >> n >> m;
  if (n == 1) {
    cout << "1\n1\n1\n";
    return;
  }
  vec<int> a(m);
  vec<int> odds;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
    if (a[i] % 2) {
      odds.push_back(i);
    }
  }
  if (odds.size() > 2) {
    cout << "Impossible\n";
  } else {
    if (odds.size() >= 1) {
      swap(a[0], a[odds[0]]);
    }
    if (odds.size() >= 2) {
      swap(a[m - 1], a[odds[1]]);
    }
    for (int i = 0; i < m; i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
    if (m == 1) {
      cout << "2\n";
      cout << a[0] - 1 << ' ' << 1 << '\n';
    } else {
      vec<int> ans;
      ans.push_back(a[0] - 1);
      if (ans.front() == 0)
        ans.pop_back();
      for (int i = 1; i < m - 1; i++) {
        ans.push_back(a[i]);
      }
      ans.push_back(a.back() + 1);
      cout << ans.size() << '\n';
      for (auto el : ans) {
        cout << el << ' ';
      }
      cout << '\n';
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



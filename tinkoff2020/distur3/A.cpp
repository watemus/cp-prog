//
// Created by watemus on 23.10.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
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

void run() {
  int n;
  cin >> n;
  map<int, vec<int>> mp;
  for (int i = 0; i < n; i++) {
    int el;
    cin >> el;
    if (mp.count(el)) {
      mp[el].push_back(i);
    } else {
      mp[el] = {i};
    }
  }
  if (n % 2) {
    cout << "0\n";
    return;
  }
  int ans = n;
  for (auto valvc : mp) {
    auto &val = valvc.first;
    auto &vc = valvc.second;
    if (vc.size() == 1) continue;
    for (auto val : vc) {
      auto it = lower_bound(ALL(vc), n - val - 1);
      if (it != vc.end() && *it != val) {
        ans = min(ans, abs(*it - (n - val - 1)));
      }
      if (it != vc.begin() && *prev(it) != val) {
        ans = min(ans, abs(*prev(it) - (n - val - 1)));
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



//
// Created by watemus on 05.08.2020.
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
  int n;
  cin >> n;
  string s;
  cin >> s;
  vec<int> nums[2];
  int have = 0;
  vec<int> ans;
  for (auto ch : s) {
    if (nums[!(ch - '0')].size()) {
      nums[ch - '0'].push_back(nums[!(ch - '0')].back());
      nums[!(ch - '0')].pop_back();
      ans.push_back(nums[ch - '0'].back());
    } else {
      have++;
      nums[ch - '0'].push_back(have);
      ans.push_back(have);
    }
  }
  cout << have << '\n';
  for (auto el : ans ) {
    cout << el << ' ';
  }
  cout << '\n';
}

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



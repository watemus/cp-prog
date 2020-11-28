//
// Created by watemus on 25.10.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'069;
constexpr int INFI = 1'000'000'069;
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

pair<int, int> rlx(pair<int, int> pr, int val) {
  pr.first = min(pr.first, val);
  pr.second = max(pr.second, val);
  return pr;
}

void chmin(pair<int, int> &a, pair<int, int> b) {
  if (b.second - b.first < a.second - a.first) {
    a = b;
  }
}

int gt(pair<int, int> a) {
  return a.second - a.first;
}

void run() {
  vec<int> a(6);
  for (int &i :a) cin >> i;
  int n;
  cin >> n;
  vec<int> b(n);
  for (int i = 0; i < n; i++) cin >> b[i];
  vec<pair<int, int>> bs;
  for (int i = 0; i < n; i++) {
    for (auto j : a) {
      bs.emplace_back(b[i] - j, i);
    }
  }
  sort(ALL(bs));
  int ans = INFI;
  int r = 0;
  map<int,int> st;
  int cnt;
  for (int l = 0; l < bs.size(); l++) {
    while (r < bs.size() && st.size() < n) {
      st[bs[r].second]++;
      r++;
    }
    if (st.size() == n) {
      ans = min(bs[r - 1].first - bs[l].first, ans);
    }
    st[bs[l].second]--;
    if (st[bs[l].second] == 0) st.erase(bs[l].second);
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



//
// Created by watemus on 30.07.2020.
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

struct Segment {
  int l, r, t;
};

void run() {
  int n;
  cin >> n;
  vec<Segment> segments(n);
  for (auto &[l, r, t] : segments) {
    int tl, tr;
    cin >> tl >> tr >> t;
    if (t == 1) {
      l = tl;
      r = -tr;
    } else {
      l = tr;
      r = -tl;
    }
  }
  sort(ALL(segments), [](const auto &a, const auto &b){
    return tie(a.l, a.t, a.r) < tie(b.l, b.t, b.r);
  });
  multiset<int> rs;
  int matching_size = 0;
  for (auto [l, r, t] : segments) {
    if (t == 2) {
      auto it = rs.upper_bound(r);
      if (it != rs.begin()) {
        rs.erase(prev(it));
        matching_size++;
      }
    } else {
      rs.insert(r);
    }
  }
  cout << n - matching_size << '\n';
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


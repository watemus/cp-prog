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

void run() {
  int n, m;
  cin >> n >> m;
  bool swapped = false;
  vec<vec<int>> rows(n, vec<int>(m));
  for (int i = 0; i < n; i++) {
    for (int &el : rows[i]) cin >> el;
  }
  vec<vec<int>> cols(m, vec<int>(n));
  for (auto &col : cols) {
    for (auto &el : col) cin >> el;
  }
  if (n > m) {
    swap(cols, rows);
    swap(n, m);
    swapped = true;
  }
  set<int> usd;
  for (auto el : cols[0]) usd.insert(el);
  int tt = 0;
  for (int i = 0; i < m; i++) {
    if (usd.count(rows[0][i])) {
      tt = i;
      break;
    }
  }
  map<pair<int, int>, bool> rel;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      rel[{cols[0][i], cols[0][j]}] = (i < j);
    }
  }
  sort(ALL(rows), [&](const auto &el1, const auto &el2){
    return rel[{el1[tt], el2[tt]}];
  });
  if (swapped) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cout << rows[j][i] << ' ';
      }
      cout << '\n';
    }
  } else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << rows[i][j] << ' ';
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



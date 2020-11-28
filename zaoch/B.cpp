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
  int n, m, k;
  cin >> n >> m >> k;
  vec<int> vc(m);
  iota(ALL(vc), 1);;
  vec<int> cnt(n);
  vec<vec<int>> ans(1, vec<int>(n));
  int row = 0;
  int col = 0;
  int hv = 0;
  while (true) {
    ans[row][col] = vc[hv];
    cnt[col]++;
    hv++;
    col++;
    if (col == n && cnt[col - 1] == k) {
      break;
    }
    if (hv == m && col == n) {
      rotate(vc.begin(), vc.begin() + 1, vc.end());
    }
    if (hv == m) {
      ans.push_back(vec<int>(n));
      row++;
      hv = 0;
    }
    if (col == n) {
      col = 0;
    }
  }
  cout << ans.size() << '\n';
  for (auto &row : ans) {
    for (auto el : row) {
      cout << el << ' ';
    }
    cout << '\n';
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



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
  int n;
  cin >> n;
  vec<vec<char>> f(n, vec<char>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> f[i][j];
    }
  }
  int cx[3] = {0, 0, 0}, co[3] = {0, 0, 0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (f[i][j] == 'X') {
        cx[(i + j) % 3]++;
      } else if (f[i][j] == 'O') {
        co[(i + j) % 3]++;
      }
    }
  }
  int ax = 0;
  int ao = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == j) continue;
      if (cx[i] + co[j] < cx[ax] + co[ao]) {
        ax = i;
        ao = j;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (f[i][j] == '.') continue;
      if ((i + j) % 3 == ax) {
        f[i][j] = 'O';
      } else if ((i + j) % 3 == ao) {
        f[i][j] = 'X';
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << f[i][j];
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



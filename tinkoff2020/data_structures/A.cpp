//
// Created by watemus on 03.10.2020.
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

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

const int N = 200;

int t[N][N][N];

void modify(int x, int y, int z, int dt) {
  for (int i = x; i < N; i += (i & -i)) {
    for (int j = y; j < N; j += (j & -j)) {
      for (int k = z; k < N; k += (k & -k)) {
        t[i][j][k] += dt;
      }
    }
  }
}

int get(int x, int y, int z) {
  int ans = 0;
  for (int i = x; i > 0; i -= (i & -i)) {
    for (int j = y; j > 0; j -= (j & -j)) {
      for (int k = z; k > 0; k -= (k & -k)) {
        ans += t[i][j][k];
      }
    }
  }
  return ans;
}

int get(int x1, int y1, int z1, int x2, int y2, int z2) {
  return get(x2, y2, z2)
    - get(x1, y2, z2)
    - get(x2, y1, z2)
    - get(x2, y2, z1)
    + get(x1, y1, z2)
    + get(x1, y2, z1)
    + get(x2, y1, z1)
    - get(x1, y1, z1);
}

void run() {
  int n;
  cin >> n;
  int q;
  while (true) {
    cin >> q;
    if (q == 3)
      break;
    if (q == 1) {
      int x, y, z, dt;
      cin >> x >> y >> z >> dt;
      x++, y++, z++;
      modify(x, y, z, dt);
    } else {
      int x1, y1, z1, x2, y2, z2;
      cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
      x2++, y2++, z2++;
      cout << get(x1, y1, z1, x2, y2, z2) << "\n";
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



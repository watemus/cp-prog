//
// Created by watemus on 06.10.2020.
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

#ifdef LOCAL
#else
#endif

const int N = 1 << 16;
const int M = 3e5 + 10;
const int D = 50;
const int LOG_N = 16;

vec<pair<int, int>> rs[LOG_N + 1][N + 1];
int t[D][N + 1];
int a[N][3];
int fl[N * 2 + 10];
int ans[M];

int n, m, d;

void gen_fl() {
  for (int i = 1; i < N; i++) {
    for (int j = LOG_N - 1; j >= 0; j--) {
      if (i & (1 << j)) {
        fl[i] = LOG_N - 1 - j;
        break;
      }
    }
  }
}

void build(int v, int l, int r) {
  if (r - l == 1)
    return;
  int mid = (l + r) / 2;
  for (int i = 0; i < d; i++) {
    t[i][mid - 1] = t[i][mid] = -1;
  }
  t[a[mid - 1][0] % d][mid - 1] = max(t[a[mid - 1][0] % d][mid - 1], a[mid - 1][0]);
  t[a[mid - 1][1] % d][mid - 1] = max(t[a[mid - 1][1] % d][mid - 1], a[mid - 1][1]);
  t[a[mid - 1][2] % d][mid - 1] = max(t[a[mid - 1][2] % d][mid - 1], a[mid - 1][2]);
  t[a[mid][0] % d][mid] = max(t[a[mid][0] % d][mid], a[mid][0]);
  t[a[mid][1] % d][mid] = max(t[a[mid][1] % d][mid], a[mid][1]);
  t[a[mid][2] % d][mid] = max(t[a[mid][2] % d][mid], a[mid][2]);
  for (int i = mid + 1; i < r; i++) {
    for (int k = 0; k < d; k++) {
      t[k][i] = -1;
    }
    for (int k = 0; k < d; k++) {
      if (t[k][i - 1] == -1)
        continue;
      t[(k + a[i][0]) % d][i] = max(t[(k + a[i][0]) % d][i], t[k][i - 1] + a[i][0]);
      t[(k + a[i][1]) % d][i] = max(t[(k + a[i][1]) % d][i], t[k][i - 1] + a[i][1]);
      t[(k + a[i][2]) % d][i] = max(t[(k + a[i][2]) % d][i], t[k][i - 1] + a[i][2]);
    }
  }
  for (auto [rb, j] : rs[v][mid - 1]) {
    for (int k = 0; k < d; k++) {
      if (t[k][mid - 1] != -1 && t[(d - k) % d][rb] != -1) {
        ans[j] = max(ans[j], t[k][mid - 1] + t[(d - k) % d][rb]);
      }
    }
  }
  for (int i = mid - 2; i >= l; i--) {
    for (int k = 0; k < d; k++) {
      t[k][i] = -1;
    }
    for (int k = 0; k < d; k++) {
      if (t[k][i + 1] == -1)
        continue;
      t[(k + a[i][0]) % d][i] = max(t[(k + a[i][0]) % d][i], t[k][i + 1] + a[i][0]);
      t[(k + a[i][1]) % d][i] = max(t[(k + a[i][1]) % d][i], t[k][i + 1] + a[i][1]);
      t[(k + a[i][2]) % d][i] = max(t[(k + a[i][2]) % d][i], t[k][i + 1] + a[i][2]);
    }
    for (auto [rb, j] : rs[v][i]) {
      for (int k = 0; k < d; k++) {
        if (t[k][i] != -1 && t[(d - k) % d][rb] != -1) {
          ans[j] = max(ans[j], t[k][i] + t[(d - k) % d][rb]);
        }
      }
    }
  }
  build(v + 1, l, mid);
  build(v + 1, mid, r);
}

void run() {
  cin >> n >> d;
  memset(ans, -1, sizeof ans);
  for (int i = 0; i < D; i++) {
    memset(t[i], -1, sizeof t[i]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> a[i][j];
    }
  }
  gen_fl();
  cin >> m;
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    if (r != l) {
      rs[fl[l ^ r]][l].emplace_back(r, i);
    } else {
      for (int j = 0; j < 3; j++) {
        if (a[l][j] % d == 0) {
          ans[i] = max(ans[i], a[l][j]);
        }
      }
    }
  }
  build(0, 0, N);
  for (int i = 0; i < m; i++) {
    cout << ans[i] << '\n';
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

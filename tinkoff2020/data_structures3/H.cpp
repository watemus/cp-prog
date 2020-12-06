//
// Created by watemus on 04.12.2020.
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

const int N = 1 << 18;
const int MOD = 998244353;

int pw(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
      ans %= MOD;
    }
    a *= a;
    a %= MOD;
    b >>= 1;
  }
  return ans;
}

namespace fft {

  void ntt(int *s, int *ans, int n, int t, int a, int b, int c) {
    if (n == 1) {
      ans[c] = s[a];
    } else {
      ntt(s, ans, n / 2, t * t % MOD, a, b * 2, c);
      ntt(s, ans, n / 2, t * t % MOD, a + b, b * 2, c + n / 2);
      int x = 1;
      for (int i = c; i < c + n / 2; i++) {
        int an1 = ans[i];
        int an2 = ans[i + n / 2];
        ans[i] = (an1 + x * an2) % MOD;
        ans[i + n / 2] = ((an1 - x * an2) % MOD + MOD) % MOD;
        x *= t;
        x %= MOD;
      }
    }
  }

  int c1[N + 10];
  int c2[N + 10];

  void convolution(int *a, int *b, int *c, int logn) {
    int n = 1 << logn;
    int w = pw(31, pw(2, 23 - logn));
    ntt(a, c1, n, w, 0, 1, 0);
    ntt(b, c2, n, w, 0, 1, 0);
    for (int i = 0; i < n; i++) {
      c1[i] = (c1[i] * c2[i]) % MOD;
    }
    ntt(c1, c, n, pw(w, MOD - 2), 0, 1, 0);
    int rev = pw(n, MOD - 2);
    for (int i = 0; i < n; i++) {
      c[i] = c[i] * rev % MOD;
    }
  }
}  //  namespace fft

vec<int> g[N + 10];

int usd[N + 10];
int sz[N + 10];

int calc_sz(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (!usd[v] && v != p) {
      sz[u] += calc_sz(v, u);
    }
  }
  return sz[u];
}

int find_centroid(int u, int p, int all_sz) {
  for (auto v : g[u]) {
    if (!usd[v] && v != p && sz[v] > all_sz / 2) {
      return find_centroid(v, u, all_sz);
    }
  }
  return u;
}

int usd_dist[N + 10];
int dist[N + 10];

int calc_dist(int u, int p, int dep, int root) {
  if (usd_dist[dep] != root) {
    usd_dist[dep] = root;
    dist[dep] = 1;
  } else {
    dist[dep]++;
  }
  int ans = dep;
  for (auto v : g[u]) {
    if (!usd[v] && p != v) {
      ans = max(ans, calc_dist(v, u, dep + 1, root));
    }
  }
  return ans;
}

int ans[N + 10];
int cans[N + 10];

void make_decomp(int u) {
  int all_sz = calc_sz(u, u);
  u = find_centroid(u, u, all_sz);
  int depth = calc_dist(u, u, 0, u);
  int logd = 0;
  while (depth > 0) {
    depth /= 2;
    logd++;
  }
  logd += 2;
  for (int i = 0; i < (1 << logd); i++) {
    if (usd_dist[i] != u) {
      dist[i] = 0;
    }
  }
  fft::convolution(dist, dist, cans, logd);
  for (int i = 0; i < (1 << logd); i++) {
    ans[i] += cans[i];
    dist[i] = 0;
  }
  for (auto v : g[u]) {
    if (!usd[v]) {
      depth = calc_dist(v, u, 1, u);
      logd = 0;
      while (depth > 0) {
        logd++;
        depth /= 2;
      }
      logd += 2;
      for (int i = 0; i < (1 << logd); i++) {
        if (usd_dist[i] != u) {
          dist[i] = 0;
        }
      }
      fft::convolution(dist, dist, cans, logd);
      for (int i = 0; i < (1 << logd); i++) {
        ans[i] -= cans[i];
        dist[i] = 0;
      }
    }
  }
  usd[u] = 1;
  for (auto v : g[u]) {
    if (!usd[v]) {
      make_decomp(v);
    }
  }
}

void run() {
  int n;
  cin >> n;
  memset(usd_dist, -1, sizeof usd_dist);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  make_decomp(0);
//  cerr << pw(31, 1 << 23) << endl;
  for (int i = 1; i < n; i++) {
    cout << ans[i] / 2 << '\n';
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



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

void run() {
  int n, m, p;
  cin >> n >> m >> p;
  vec<int> a(n), b(m);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    ans = max(a[i], ans);
  }
  for (int i = 0; i < m; i++) {
    cin >> b[i];
    ans = max(ans, b[i]);
  }
  auto g = Vec(n, 0, 0);
  for (int i = 0; i < p; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
  }
  auto dpa = a, dpb = b;
  for (int i = 0; i < n; i++) {
    sort(ALL(g[i]));
  }
  for (int i = 0; i < n; i++) {
    for (auto u : g[i]) {
      int na = dpb[u] + a[i];
      int nb = dpa[i] + b[u];
      dpb[u] = max(nb, dpb[u]);
      dpa[i] = max(na, dpa[i]);
      ans = max({ans, dpb[u], dpa[i]});
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}
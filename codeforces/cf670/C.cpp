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

void calc_sz(int v, int p, vec<vec<int>> &g, vec<int> &sz, vec<int> &msz, vec<int> &pr, int n) {
  pr[v] = p;
  sz[v] = 1;
  for (auto u : g[v]) {
    if (u != p) {
      calc_sz(u, v, g, sz, msz, pr, n);
      msz[v] = max(sz[u], msz[v]);
      sz[v] += sz[u];
    }
  }
  msz[v] = max(msz[v], n - sz[v]);
}

int find_one(int v, int p, vec<vec<int>> &g) {
  if (g[v].size() == 1)
    return v;
  for (auto u : g[v]) {
    if (u != p)
      return find_one(u, v, g);
  }
  return v;
};

void run() {
  int n;
  cin >> n;
  vec<vec<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int root = 0;
  for (int i = 0; i < n; i++) {
    if (g[i].size() > 1) {
      root = i;
      break;
    }
  }
  vec<int> pr(n), sz(n), msz(n);
  calc_sz(root, -1, g, sz, msz, pr, n);
  vec<int> ans;
  int csz = INFL;
  for (int i = 0; i < n; i++) {
    if (msz[i] < csz) {
      ans = {i};
      csz = msz[i];
    } else if (msz[i] == csz) {
      ans.push_back(i);
    }
  }
  if (ans.size() == 1) {
    cout << root + 1 << ' ' << g[root][0] + 1 << '\n';
    cout << root + 1 << ' ' << g[root][0] + 1 << '\n';
    return;
  }else if (ans.size() == 2) {
    
    int cv = find_one(ans[0], ans[1], g);
    cout << cv + 1 << ' ' << pr[cv] + 1 << '\n';
    cout << cv + 1 << " " << ans[1] + 1 << '\n';
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


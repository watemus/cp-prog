//
// Created by watemus on 20.11.2020.
//

//
// Created by watemus on 19.11.2020.
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

const int N = 1e5;

vec<int> g[N];

int sz[N];

void set_sz(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v != p) {
      set_sz(v, u);
      sz[u] += sz[v];
    }
  }
}

string s, t;

int dfs(int u, int p, int dep) {
  if (dep == s.size()) {
    return 0;
  } else if (t[u] < s[dep]) {
    return sz[u];
  } else if (t[u] == s[dep]) {
    int ans = 1;
    for (auto v : g[u]) {
      if (v != p) {
        ans += dfs(v, u, dep + 1);
      }
    }
    return ans;
  }
  return 0;
}

void run() {
  int n, m;
  cin >> n >> m;
  cin >> s >> t;
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    p--;
    g[p].push_back(i);
    g[i].push_back(p);
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    set_sz(i, i);
    ans += dfs(i, i, 0);
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
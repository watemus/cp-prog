//
// Created by watemus on 08.10.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
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

const int N = 2e5 + 10;
int t[N];

void add(int at) {
  for (int i = at; i < N; i += (i & -i)) {
    t[i]++;
  }
}

int get(int at) {
  int ans = 0;
  for (int i = at; i > 0; i -= (i & -i)) {
    ans += t[i];
  }
  return ans;
}

vec<int> g[N];
int ans = 0;

void dfs(int v, int nn) {
  add(v + 1);
  ans += get(nn) - get(v + 1);
  for (auto u : g[v]) {
    dfs(u, nn);
  }
}

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    for (int j = 0; j < m; j++) {
      int u;
      cin >> u;
      g[i].push_back(u - 1);
    }
  }
  if (n > 5000) {
    dfs(0, N - 1);
    cout << ans << ' ';
    for (int i = 1; i < n; i++) {
      cout << "0 ";
    }
  } else {
    for (int i = 0; i < n; i++) {
      memset(t, 0, sizeof(int) * (5010));
      dfs(i, 5010);
      cout << ans << ' ';
      ans = 0;
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

//
// Created by watemus on 02.11.2020.
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

struct Way {
  int cnt_inv, moves, v, inv;
};

const int LOG = 20;

bool operator<(const Way &a, const Way &b) {
  if (a.cnt_inv < LOG && b.cnt_inv < LOG) {
    if ((1LL << a.cnt_inv) - 1 + a.moves == (1LL << b.cnt_inv) - 1 + b.moves)
      return a.cnt_inv < b.cnt_inv;
    return (1LL << a.cnt_inv) - 1 + a.moves < (1LL << b.cnt_inv) - 1 + b.moves;
  }
  return pair(a.cnt_inv, a.moves) < pair(b.cnt_inv, b.moves);
}

const int N = 2e5 + 10;

vec<int> g[N], rg[N];

const int mod = 998244353;

void run() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    rg[v].push_back(u);
  }
  multiset<Way> st;
  st.insert({0, 0, 0, 0});
  vec<vec<Way>> dist(n, vec<Way>(LOG * 2 + 2, {INFI, 0, 0, 0}));
  vec<vec<int>> usd(n, vec<int>(LOG * 2 + 2, 0));
  vec<vec<int>> ddist(n, vec<int>(2, 0));
  auto ttoo = [](int cnt_inv, int inv) {
    return min(LOG, cnt_inv) * 2 + inv;;
  };
  while (st.size()) {
    auto [cnt_inv, moves, v, inv] = *st.begin();
    st.erase(st.begin());
    int sinv = ttoo(cnt_inv, inv);
    if (usd[v][sinv])
      continue;
    usd[v][sinv] = 1;
    for (int i = sinv; i < usd[v].size(); i += 2) {
      usd[v][i] = 1;
    }
    dist[v][sinv] = {cnt_inv, moves, v, inv};
    for (auto u : g[v]) {
      if (!usd[u][ttoo(cnt_inv + inv, 0)]) {
        st.insert({cnt_inv + inv, moves + 1, u, 0});
      }
    }
    for (auto u : rg[v]) {
      if (!usd[u][ttoo(cnt_inv + inv, 1)]) {
        st.insert({cnt_inv + !inv, moves + 1, u, 1});
      }
    }
  }
  Way ans = dist[n - 1][0];
  for (int i = 1; i < dist[n - 1].size(); i++) {
    ans = min(ans, dist[n - 1][i]);
  }
  int ansik = ans.moves;
  int p = 1;
  for (int i = 0; i < ans.cnt_inv; i++) {
    ansik += p;
    ansik %= mod;
    p *= 2;
    p %= mod;
  }
  cout << ansik << '\n';
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



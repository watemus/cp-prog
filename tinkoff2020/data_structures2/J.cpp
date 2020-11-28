//
// Created by watemus on 24.10.2020.
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

// #define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'069;
constexpr int INFI = 1'000'000'069;
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

const int T = 1e7;
const int N = 2e5 + 10;

int t[T], lt[T], rt[T];

int cnt_nodes = 0;

inline int new_node() {
  return cnt_nodes++;
}

inline int cpy_node(int u) {
  int v = new_node();
  t[v] = t[u];
  lt[v] = lt[u];
  rt[v] = rt[u];
  return v;
}

int get(int v, int at) {
  int l = 0;
  int r = N;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (at < mid) {
      v = lt[v];
      r = mid;
    } else {
      v = rt[v];
      l = mid;
    }
  }
  return t[v];
}

void modify(int v, int at, int val) {
  int l = 0;
  int r = N;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (at < mid) {
      if (lt[v] == -1)
        lt[v] = new_node();
      else
        lt[v] = cpy_node(lt[v]);
      v = lt[v];
      r = mid;
    } else {
      if (rt[v] == -1)
        rt[v] = new_node();
      else
        rt[v] = cpy_node(rt[v]);
      v = rt[v];
      l = mid;
    }
  }
  t[v] = val;
}

int front[N], len[N];
int root[N];

void run() {
  memset(lt, -1, sizeof lt);
  memset(rt, -1, sizeof rt);
  int n;
  cin >> n;
  root[0] = new_node();
  for (int i = 1; i <= n; i++) {
    int typ, from;
    cin >> typ >> from;
    root[i] = cpy_node(root[from]);
    front[i] = front[from];
    len[i] = len[from];
    if (typ == 1) {
      int m;
      cin >> m;
      modify(root[i], len[i], m);
      len[i]++;
    } else {
      cout << get(root[i], front[i]) << '\n';
      front[i]++;
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



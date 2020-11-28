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

// #define int ll

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

const int T = 1e7;

int t[T], lt[T], rt[T];
int cnt_nodes = 0;
const int S = 3e5 + 10;

int new_node() {
  int v = cnt_nodes++;
  t[v] = 0;
  lt[v] = -1;
  rt[v] = -1;
  return v;
}

int cpy_node(int u) {
  int v = cnt_nodes++;
  t[v] = t[u];
  lt[v] = lt[u];
  rt[v] = rt[u];
  return v;
}

void build(int v, int l, int r) {
  if (r - l > 1) {
    lt[v] = new_node();
    rt[v] = new_node();
    int mid = (l + r) / 2;
    build(lt[v], l, mid);
    build(rt[v], mid, r);
  }
}

int modify(int v, int l, int r, int at, int val) {
  v = cpy_node(v);
  if (r - l == 1) {
    t[v] = val;
  } else {
    int mid = (l + r) / 2;
    if (at < mid) {
      lt[v] = modify(lt[v], l, mid, at, val);
    } else {
      rt[v] = modify(rt[v], mid, r, at, val);
    }
    t[v] = min(t[lt[v]], t[rt[v]]);
  }
  return v;
}

int get(int v, int l, int r, int val) {
  if (t[v] > val)
    return -1;
  if (r - l == 1)
    return l;
  int mid = l + r >> 1;
  int ans = get(lt[v], l, mid, val);
  if (ans == -1)
    return get(rt[v], mid, r, val);
  return ans;
}

void print(int v, int l, int r) {
  if (r - l == 1) {
    cout << t[v] << ' ';
  } else {
    int mid = (r + l) / 2;
    print(lt[v], l, mid);
    print(rt[v], mid, r);
  }
}

void run() {
  int n, s, m;
  cin >> n >> s >> m;
  vec<int> coords;
  vec<tuple<int, int, int>> passengers(m);
  for (auto &[c, l, r] : passengers) {
    cin >> c >> l >> r;
    l++;
    c--;
    coords.push_back(l);
    coords.push_back(r);
  }
  coords.push_back(0);
  sort(ALL(coords));
  coords.resize(unique(ALL(coords)) - coords.begin());
  map<int, int> to;
  for (int i = 0; i < coords.size(); i++) {
    to[coords[i]] = i;
  }
  vec<vec<int>> ls(coords.size()), rs(coords.size());
  for (auto [c, l, r] : passengers) {
    ls[to[l]].push_back(c);
    rs[to[r]].push_back(c);
  }
  vec<int> roots(coords.size());
  roots[0] = new_node();
  build(roots[0], 0, s);
  for (int i = 0; i < coords.size(); i++) {
    if (i > 0)
      roots[i] = cpy_node(roots[i - 1]);
    for (int j : ls[i]) {
      roots[i] = modify(roots[i], 0, s, j, INFI);
    }
    for (int j : rs[i]) {
      roots[i] = modify(roots[i], 0, s, j, coords[i]);
    }
//    print(roots[i], 0, s);
//    cout << endl;
  }
  int q;
  cin >> q;
  int p = 0;
  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    a += p;
    b += p;
    int sb = upper_bound(ALL(coords), b) - coords.begin() - 1;
    p = get(roots[sb], 0, s, a) + 1;
    cout << p << '\n';
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



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

#define int ll

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

const int T = 1.6e7;
const int N = 5e5;

signed t[T], lt[T], rt[T];

int cnt_nodes = 0;

int new_node() {
  assert(cnt_nodes < T);
  return cnt_nodes++;
}

int cpy_node(int u) {
  int v = new_node();
  lt[v] = lt[u];
  rt[v] = rt[u];
  t[v] = t[u];
  return v;
}

const int LOG_N = 40;

int st[LOG_N];

void add(int v, int at) {
  int l = 0;
  int r = N;
  int ptr = 0;
  while (l + 1 < r) {
    ptr++;
    t[v]++;
    int mid = (l + r) / 2;
    if (at < mid) {
      if (lt[v] == -1) {
        lt[v] = new_node();
      } else {
        lt[v] = cpy_node(lt[v]);
      }
      v = lt[v];
      r = mid;
    } else {
      if (rt[v] == -1) {
        rt[v] = new_node();
      } else {
        rt[v] = cpy_node(rt[v]);
      }
      v = rt[v];
      l = mid;
    }
  }
  t[v]++;
}

int descent(int v1, int v2, int k) {
  int l = 0;
  int r = N;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (lt[v1] == -1) lt[v1] = new_node();
    if (lt[v2] == -1) lt[v2] = new_node();
    int cnt_l = t[lt[v2]] - t[lt[v1]];
    if (cnt_l >= k) {
      v1 = lt[v1];
      v2 = lt[v2];
      r = mid;
    } else {
      k -= cnt_l;
      if (rt[v1] == -1) rt[v1] = new_node();
      if (rt[v2] == -1) rt[v2] = new_node();
      v2 = rt[v2];
      v1 = rt[v1];
      l = mid;
    }
  }
  return l;
}

void run() {
  memset(lt, -1, sizeof lt);
  memset(rt, -1, sizeof rt);
  int n;
  cin >> n;
  vec<signed> roots(n + 1);
  roots[0] = new_node();
  int a1, l, m;
  cin >> a1 >> l >> m;
  vec<int> a(n + 1);
  vec<int> coords;
  a[1] = a1;
  coords.push_back(a1);
  for (int i = 2; i <= n; i++) {
    a[i] = (a[i - 1] * l + m) % ll(1e9);
    coords.push_back(a[i]);
  }
  sort(ALL(coords));
  coords.resize(unique(ALL(coords)) - coords.begin());
  umap<int, int> to, from;
  to.reserve(coords.size());
  from.reserve(coords.size());
  for (int i = 0; i < coords.size(); i++) {
    to[coords[i]] = i;
    from[i] = coords[i];
  }
  for (int i = 1; i <= n; i++) {
    a[i] = to[a[i]];
  }
  roots[1] = cpy_node(roots[0]);
  add(roots[1], a[1]);
  for (int i = 2; i <= n; i++) {
    roots[i] = cpy_node(roots[i - 1]);
    add(roots[i], a[i]);
  }
  int B;
  cin >> B;
  int ans = 0;
  while (B--) {
    int G;
    cin >> G;
    int x1, lx, mx;
    cin >> x1 >> lx >> mx;
    int y1, ly, my;
    cin >> y1 >> ly >> my;
    int k1, lk, mk;
    cin >> k1 >> lk >> mk;
    for (int i = 0; i < G; i++) {
      int lb = min(x1, y1);
      int rb = max(x1, y1);
      ans += from[descent(roots[lb - 1], roots[rb], k1)];
      x1 = ((lb - 1) * lx + mx) % n + 1;
      y1 = ((rb - 1) * ly + my) % n + 1;
      k1 = ((k1 - 1) * lk + mk) % (abs(x1 - y1) + 1) + 1;
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



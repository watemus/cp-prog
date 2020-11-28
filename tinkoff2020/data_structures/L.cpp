//
// Created by watemus on 27.10.2020.
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

const int N = 3e6;

int val[N], prior[N], lt[N], rt[N], sz[N], agn[N];

int cnt_nodes = 0;

int new_node(int _val) {
  int v = cnt_nodes++;
  val[v] = _val;
  prior[v] = rnd();
  lt[v] = -1;
  rt[v] = -1;
  sz[v] = 1;
  agn[v] = 0;
  return v;
}

int size(int v) {
  if (v != -1)
    return sz[v];
  return 0;
}

void push(int v) {
  if (v != -1) {
    val[v] += agn[v];
    if (lt[v] != -1) agn[lt[v]] += agn[v];
    if (rt[v] != -1) agn[rt[v]] += agn[v];
    agn[v] = 0;
  }
}

void pull(int v) {
  if (v != -1) {
    sz[v] = 1 + size(lt[v]) + size(rt[v]);
  }
}

pair<int, int> split_sz(int v, int szz) {
  if (v == -1) return {-1, -1};
  push(v);
  if (size(lt[v]) >= szz) {
    auto [l, r] = split_sz(lt[v], szz);
    pull(l);
    pull(r);
    lt[v] = r;
    pull(v);
    return {l, v};
  } else {
    auto [l, r] = split_sz(rt[v], szz - size(lt[v]) - 1);
    pull(l);
    pull(r);
    rt[v] = l;
    pull(v);
    return {v, r};
  }
}

pair<int, int> split_key(int v, int key) {
  if (v == -1) return {-1, -1};
  push(v);
  if (key > val[v]) {
    auto [l, r] = split_key(lt[v], key);
    pull(l);
    pull(r);
    lt[v] = r;
    pull(v);
    return {l, v};
  } else {
    auto [l, r] = split_key(rt[v], key);
    pull(l);
    pull(r);
    rt[v] = l;
    pull(v);
    return {v, r};
  }
}

int merge(int l, int r) {
  if (l == -1) return r;
  if (r == -1) return l;
  push(l);
  push(r);
  if (prior[l] < prior[r]) {
    rt[l] = merge(rt[l], r);
    pull(rt[l]);
    pull(l);
    return l;
  } else {
    lt[r] = merge(l, lt[r]);
    pull(lt[r]);
    pull(r);
    return r;
  }
}

const int G = 3e5 + 10;

void print(int v) {
  if (v == -1) return;
  push(v);
  print(rt[v]);
  if (val[v] != 0)
    cout << val[v] << ' ';
  print(lt[v]);
}

void printt(int v) {
  if (v == -1) return;
  push(v);
  printt(lt[v]);
  cout << val[v] << ' ';
  printt(rt[v]);
}

void run() {
  int vals = -1, cnts = -1;
  int n, m;
  cin >> n >> m;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(RALL(a));
  for (int i = 0; i < n; i++) {
    vals = merge(vals, new_node(a[i]));
  }
//  print(vals);
//  cout << endl;
  while (size(vals) < G) {
    vals = merge(vals, new_node(0));
//    print(vals);
//    cout << endl;
  }
  for (int i = 0; i < G; i++) {
    cnts = merge(cnts, new_node(0));
//    print(cnts);
//    cout << endl;
  }
  for (auto el : a) {
    auto [l, r] = split_sz(cnts, el);
    agn[l]++;
//    print(l);
//    cout << endl;
//    cout << sz[l] << endl;
    cnts = merge(l, r);
//    print(cnts);
//    cout << endl;
  }
  auto get_cnt = [&](int el) {
    auto [l, mmmr] = split_sz(cnts, el - 1);
    auto [m, mmr] = split_sz(mmmr, 1);
    auto [mm, r] = split_sz(mmr, 1);
    push(mm);
    push(m);
    int ans = val[m] - val[mm];
    cnts = merge(l, merge(m, merge(mm, r)));
    return ans;
  };
  for (int i = 0; i < m; i++) {
    char typ;
    cin >> typ;
    if (typ == 't') {
      swap(vals, cnts);
    } else if (typ == 'a') {
      int x;
      cin >> x;
      auto[l, r] = split_key(vals, x);
      l = merge(l, new_node(x));
      vals = merge(l, r);
      vals = split_sz(vals, G).first;
      tie(l, r) = split_sz(cnts, x);
      agn[l]++;
      cnts = merge(l, r);
    } else if (typ == 'r') {
      int x;
      cin >> x;
//      printt(vals);
//      cout << endl;
//      printt(cnts);
//      cout << endl;
      int cnt = get_cnt(x);
      if (cnt > 0) {
        auto[l, mr] = split_key(vals, x + 1);
//        print(l);
//        cout << endl;
//        print(mr);
//        cout << endl;
        auto[m, r] = split_sz(mr, 1);
        vals = merge(l, r);
        vals = merge(vals, new_node(0));
//        print(vals);
//        cout << endl;
        tie(l, r) = split_sz(cnts, x);
        agn[l]--;
        cnts = merge(l, r);
      }
    } else {
      int x;
      cin >> x;
      cout << get_cnt(x) << '\n';
    }
//    print(vals);
//    cout << endl;
//    print(cnts);
//    cout << endl;
  }
  print(vals);
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



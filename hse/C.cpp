//
// Created by watemus on 11.11.2020.
//

#ifdef LOCAL
//#define _GLIBCXX_DEBUG
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

const int N = 1 << 20;

int t[N * 2], agn[N * 2], vll[N * 2];

void build(int v, int l, int r, vec<pair<int, int>> &arr) {
  if (r - l == 1) {
    t[v] = arr[l].second;
    agn[v] = -1;
    vll[v] = arr[l].first;
  } else {
    int mid = (l + r) / 2;
    build(v * 2 + 1, l, mid, arr);
    build(v * 2 + 2, mid, r, arr);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    agn[v] = -1;
  }
}

inline void push(int v, int l, int r) {
  if (agn[v] != -1) {
    if (r - l > 1) {
      agn[v * 2 + 1] = agn[v];
      agn[v * 2 + 2] = agn[v];
    }
    t[v] = agn[v] * (r - l);
    agn[v] = -1;
  }
}

void modify(int v, int l, int r, int lq, int rq, int val) {
  push(v, l, r);
  if (lq <= l && r <= rq) {
    agn[v] = val;
    push(v, l, r);
    return;
  }
  if (r <= lq || rq <= l)
    return;
  int mid = (l + r) / 2;
  modify(v * 2 + 1, l, mid, lq, rq, val);
  modify(v * 2 + 2, mid, r, lq, rq, val);
  t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

int get_kth1(int v, int l, int r, int k) {
  push(v, l, r);
  if (k > t[v])
    return -1;
  if (r - l == 1) {
    return l;
  }
  int mid = (l + r) / 2;
  int ans = get_kth1(v * 2 + 1, l, mid, k);
  if (ans == -1) {
    return get_kth1(v * 2 + 2, mid, r, k - t[v * 2 + 1]);
  }
  return ans;
}

int get_kth0(int v, int l, int r, int k) {
  push(v, l, r);
  if (k > r - l - t[v])
    return -1;
  if (r - l == 1) {
    return l;
  }
  int mid = (l + r) / 2;
  int ans = get_kth0(v * 2 + 1, l, mid, k);
  if (ans == -1) {
    return get_kth0(v * 2 + 2, mid, r, k - (mid - l - t[v * 2 + 1]));
  }
  return ans;
}

vec<int> a, b;

void make_ans(int v, int l, int r) {
  push(v, l, r);
  if (r - l == 1) {
    if (t[v])
      b.push_back(vll[v]);
    else
      a.push_back(vll[v]);
  } else {
    int mid = (l + r) / 2;
    make_ans(v * 2 + 1, l, mid);
    make_ans(v * 2 + 2, mid, r);
  }
}

void run() {
  int n;
  cin >> n;
  vec<pair<int, int>> arr;
  for (int i = 0; i < n; i++) {
    int el;
    cin >> el;
    arr.emplace_back(el, 0);
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int el;
    cin >> el;
    arr.emplace_back(el, 1);
  }
  sort(ALL(arr));
  build(0, 0, n + m, arr);
  int q;
  cin >> q;
  while (q--) {
    int tp, l, r;
    cin >> tp >> l >> r;
    int rr, ll;
    if (tp == 1) {
      ll = get_kth0(0, 0, n + m, l);
      rr = get_kth0(0, 0, n + m, r);
      modify(0, 0, n + m, ll, rr + 1, 1);
    } else {
      ll = get_kth1(0, 0, n + m, l);
      rr = get_kth1(0, 0, n + m, r);
      modify(0, 0, n + m, ll, rr + 1, 0);
    }
  }
  make_ans(0, 0, n + m);
  cout << a.size() << "\n";
  for (auto el : a) {
    cout << el << ' ';
  }
  cout << '\n' << b.size() << '\n';
  for (auto el : b) {
    cout << el << ' ';
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



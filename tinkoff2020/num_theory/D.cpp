//
// Created by watemus on 29.09.2020.
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

constexpr int MAXN = 5e4 + 10;

int t[MAXN * 4];
int agn[MAXN * 4];

void build(int v, int l, int r) {
  if (r - l == 1) {
    t[v] = 0;
    agn[v] = 0;
  } else {
    int mid = (l + r) / 2;
    build(v * 2 + 1, l, mid);
    build(v * 2 + 2, mid, r);
  }
}

void push(int v, int l, int r) {
  if (r - l > 1) {
    agn[v * 2 + 1] += agn[v];
    agn[v * 2 + 2] += agn[v];
  }
  t[v] += agn[v];
  agn[v] = 0;
}

void add(int v, int l, int r, int lt, int rt, int x) {
  push(v, l, r);
  if (lt <= l && r <= rt) {
    agn[v] += x;
  } else {
    int mid = (l + r) / 2;
    if (lt < mid)
      add(v * 2 + 1, l, mid, lt, rt, x);
    if (mid < rt)
      add(v * 2 + 2, mid, r, lt, rt, x);
    push(v * 2 + 1, l, mid);
    push(v * 2 + 2, mid, r);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
  }
}

int get(int v, int l, int r, int lt, int rt) {
  push(v, l, r);
  if (lt <= l && r <= rt) {
    return t[v];
  } else {
    int ans = 0;
    int mid = (l + r) / 2;
    if (lt < mid) {
      ans = max(ans, get(v * 2 + 1, l, mid, lt, rt));
    }
    if (mid < rt) {
      ans = max(ans, get(v * 2 + 2, mid, r, lt, rt));
    }
    return ans;
  }
}

void print_st(int v, int l, int r) {
  push(v, l, r);
  int mid = (l + r) / 2;
  if (r - l > 1) {
    print_st(v * 2 + 1, l, mid);
    print_st(v * 2 + 2, mid, r);
  } else {
    cout << t[v] << ' ';
  }
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  a[0] = INFI;
  build(0, 0, n + 2);
  vec<pair<int, int>> ls;
  vec<int> st_mn {0}, st_mx {0};
  vec<int> cl_mx(n + 1), usd(n + 1);
  int ans = 0;
  for (int r = 1; r <= n; r++) {
    int cx = abs(a[r]);
    for (int i = ls.size() - 1; i >= 0; i--) {
      cx = gcd(ls[i].second, cx);
      ls[i].second = cx;
    }
    vec<pair<int, int>> new_ls = {{r, abs(a[r])}};
    for (int i = ls.size() - 1; i >= 0; i--) {
      if (ls[i].second == new_ls.back().second) {
        new_ls.pop_back();
      }
      new_ls.push_back(ls[i]);
    }
    reverse(ALL(new_ls));
    ls = new_ls;
    while (st_mn.back() != 0 && a[st_mn.back()] >= a[r]) {
      st_mn.pop_back();
    }
    while (st_mx.back() != 0 && a[st_mx.back()] <= a[r]) {
      add(0, 0, n + 2, st_mx[st_mx.size() - 2] + 1, st_mx.back() + 1, a[st_mx.back()]);
      st_mx.pop_back();
    }
    add(0, 0, n + 2, 0, r + 1, a[r]);
    add(0, 0, n + 2, st_mx.back() + 1, r + 1, -a[r]);
//    print_st(0, 0, n + 2);
//    cout << endl;
    cl_mx[r] = st_mx.back();
    st_mn.push_back(r);
    st_mx.push_back(r);
    for (auto [i, g] : ls) {
      // cout << "(" << i << ", " << g << ") ";
      ans = max(ans, get(0, 0, n + 2, i, r + 1) * g);
    }
    // cout << endl;
    // cout << ans << endl;
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



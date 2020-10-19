//
// Created by watemus on 09.10.2020.
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

#ifdef LOCAL
#else
#endif

const int N = 1e5;

int mn[N * 4], mn2[N * 4], sm[N * 4], cnt_mn[N * 4], agn_mn[N * 4], agn_eq[N * 4];

void push(int v, int l, int r) {
  if (agn_mn[v] != -1) {
    if (r - l > 1) {
      if (mn[v * 2 + 1] < agn_mn[v]) {
        agn_mn[v * 2 + 1] = max(agn_mn[v * 2 + 1], agn_mn[v]);
      }
      if (mn[v * 2 + 2] < agn_mn[v]) {
        agn_mn[v * 2 + 2] = max(agn_mn[v * 2 + 1], agn_mn[v]);
      }
    }
    sm[v] += (agn_mn[v] - mn[v]) * cnt_mn[v];
    mn[v] = agn_mn[v];
    agn_mn[v] = -1;
  }
}

void pull(int v, int l, int r) {
  push(v, l, r);
  if (r - l > 1) {
    int mid = (l + r) / 2;
    push(v * 2 + 1, l, mid);
    push(v * 2 + 2, mid, r);
    if (mn[v * 2 + 1] == mn[v * 2 + 2]) {
      mn[v] = mn[v * 2 + 1];
      cnt_mn[v] = cnt_mn[v * 2 + 1] + cnt_mn[v * 2 + 2];
      mn2[v] = min(mn2[v * 2 + 1], mn2[v * 2 + 2]);
    } else if (mn[v * 2 + 1] < mn[v * 2 + 2]) {
      mn[v] = mn[v * 2 + 1];
      cnt_mn[v] = cnt_mn[v * 2 + 1];
      mn2[v] = min(mn[v * 2 + 2], mn2[v * 2 + 1]);
    } else {
      mn[v] = mn[v * 2 + 2];
      cnt_mn[v] = cnt_mn[v * 2 + 2];
      mn2[v] = min(mn[v * 2 + 1], mn2[v * 2 + 2]);
    }
    sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
  }
}

int get(int v, int l, int r, int lq, int rq) {
  push(v, l, r);
  if (lq <= l && r <= rq) {
    return sm[v];
  }
  int ans = 0;
  int mid = (l + r) / 2;
  if (lq < mid)
    ans += get(v * 2 + 1, l, mid, lq, rq);
  if (mid < rq)
    ans += get(v * 2 + 2, mid, r, lq, rq);
  return ans;
}

void modify(int v, int l, int r, int lq, int rq, int x) {
  push(v, l, r);
  if (lq <= l && r <= rq) {
    if (x <= mn[v])
      return;
    if (mn[v] < x && x < mn2[v]) {
      agn_mn[v] = x;
      push(v, l, r);
    }
    if (x >= mn2[v]) {
      int mid = (l + r) / 2;
      modify(v * 2 + 1, l, mid, lq, rq, x);
      modify(v * 2 + 2, mid, r, lq, rq, x);
    }
    pull(v, l, r);
  } else {
    int mid = (l + r) / 2;
    if (lq < mid) {
      modify(v * 2 + 1, l, mid, lq, rq, x);
    }
    if (mid < rq) {
      modify(v * 2 + 2, mid, r, lq, rq, x);
    }
    pull(v, l, r);
  }
}

void print(int v, int l, int r) {
  push(v, l, r);
  if (r - l == 1) {
    cout << sm[v] << ' ';
  } else {
    int mid = (l + r) / 2;
    print(v * 2 + 1, l, mid);
    print(v * 2 + 2, mid, r);
  }
}

void build(int v, int l, int r) {
  sm[v] = 0;
  mn[v] = 0;
  agn_mn[v] = -1;
  agn_eq[v] = -1;
  mn2[v] = INFI;
  cnt_mn[v] = r - l;
  if (r - l > 1) {
    int mid = (r + l) / 2;
    build(v * 2 + 1, l, mid);
    build(v * 2 + 2, mid, r);
  }
}

int cnt = 0;

void run(int n, int m) {
  build(0, 0, n);
  for (int i = 0; i < m; i++) {
    char q;
    cin >> q;
    if (q == '^') {
      int lq, rq, x;
      cin >> lq >> rq >> x;
      modify(0, 0, n, lq - 1, rq, x);
    } else {
      int lq, rq;
      cin >> lq >> rq;
      int a = get(0, 0, n, lq - 1, rq);
      int b = rq - lq + 1;
      int g = gcd(a, b);
      a /= g;
      b /= g;
      cout << a;
      if (b != 1) {
        cout << "/" << b;
      }
      cout << '\n';
    }
    // print(0, 0, n);
    // cout << '\n';
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
  // cout << fixed << setprecision(20);
  while (t--) {
    int n, m;
    while (true) {
      cin >> n >> m;
      if (n == 0 && m == 0)
        return 0;
      run(n, m);
    }
  }
  return 0;
}



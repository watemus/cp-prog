//
// Created by watemus on 17.11.2020.
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

const int N = 2e5;
int mx[N * 4], mn[N * 4], sm[N * 4], agn[N * 4];

void build(int v, int l, int r, vec<int> &arr) {
  if (r - l == 1) {
    mx[v] = sm[v] = arr[l];
    mn[v] = arr[l];
    agn[v] = -1;
  } else {
    int mid = (l + r) / 2;
    build(v * 2 + 1, l, mid, arr);
    build(v * 2 + 2, mid, r, arr);
    mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
    mn[v] = min(mn[v * 2 + 1], mn[v * 2 + 2]);
    sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
    agn[v] = -1;
  }
}

void push(int v, int l, int r) {
  if (agn[v] != -1) {
    mx[v] = agn[v];
    mn[v] = agn[v];
    sm[v] = agn[v] * (r - l);
    if (r - l > 1) {
      int mid = (l + r) / 2;
      agn[v * 2 + 1] = agn[v * 2 + 2] = agn[v];
    }
    agn[v] = -1;
  }
}

void modify(int v, int l, int r, int lq, int rq, int x) {
  push(v, l, r);
  if (lq <= l && r <= rq) {
    agn[v] = x;
    push(v, l, r);
    return;
  }
  if (rq <= l || r <= lq)
    return;
  int mid = (l + r) / 2;
  modify(v * 2 + 1, l, mid, lq, rq, x);
  modify(v * 2 + 2, mid, r, lq, rq, x);
  mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
  sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
}

int desc(int v, int l, int r, int x) {
  push(v, l, r);
  if (mn[v] > x) {
    return r;
  }
  if (r - l == 1) {
    return l;
  }
  int mid = (l + r) / 2;
  int ans = desc(v * 2 + 1, l, mid, x);
  if (ans == mid) {
    return desc(v * 2 + 2, mid, r, x);
  }
  return ans;
}

int get(int v, int l, int r, int lq, int rq) {
  int ans = 0;
  if (lq <= l && r <= rq) {
    return sm[v];
  }
  if (rq <= l || r <= lq) {
    return 0;
  }
  int mid = (l + r) / 2;
  ans += get(v * 2 + 1, l, mid, lq, rq);
  ans += get(v * 2 + 2, mid, r, lq, rq);
  return ans;
}

pair<int, int> pizda(int v, int l, int r, int lq, int mxx) {
  push(v, l, r);
  if (lq <= l && sm[v] <= mxx) {
    return {r, mxx - sm[v]};
  }
  if (r <= lq) {
    return {lq, mxx};
  }
  if (r - l == 1) {
    return {l, mxx};
  }
  int mid = (l + r) / 2;
  auto ans = pizda(v * 2 + 1, l, mid, lq, mxx);
  mxx = ans.second;
  if (mxx && ans.first >= mid) {
    auto rans = pizda(v * 2 + 2, mid, r, lq, mxx);
    return rans;
  }
  return ans;
}

void run() {
  int n, q;
  cin >> n >> q;
  vec<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  build(0, 0, n, arr);
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      int l = desc(0, 0, n, y);
      if (l < x) {
        modify(0, 0, n, l, x, y);
      }
    } else {
      int l = desc(0, 0, n, y);
      l = max(x - 1, l);
      int oy = y;
      int ans = 0;
      while (l < n && y > 0) {
        auto [nl, mxx] = pizda(0, 0, n, l, y);
        ans += nl - l;
        l = max(nl, desc(0, 0, n, mxx));
        y = mxx;
      }
      cout << ans << '\n';
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



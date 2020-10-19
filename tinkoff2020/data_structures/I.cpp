//
// Created by watemus on 07.10.2020.
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

const int N = 2e5 + 10;

int t[N * 4], agn[N * 4];

void push(int v, int l, int r) {
  if (r - l > 1) {
    agn[v * 2 + 1] += agn[v];
    agn[v * 2 + 2] += agn[v];
  }
  t[v] += agn[v];
  agn[v] = 0;
}

void add(int v, int l, int r, int lq, int rq) {
  push(v, l, r);
  if (lq <= l && r <= rq) {
    agn[v]++;
    push(v, l, r);
  } else {
    int mid = (l + r) / 2;
    if (lq < mid) {
      add(v * 2 + 1, l, mid, lq, rq);
    }
    if (mid < rq) {
      add(v * 2 + 2, mid, r, lq, rq);
    }
    push(v * 2 + 1, l, mid);
    push(v * 2 + 2, mid, r);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
  }
}

void run() {
  int n;
  cin >> n;
  vec<int> a(n), b(n);
  map<int, vec<int>> ma, mb;
  vec<int> coords;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    coords.push_back(a[i]);
    if (ma.count(a[i])) {
      ma[a[i]].push_back(i);
    } else {
      ma[a[i]] = {i};
    }
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    coords.push_back(b[i]);
    if (mb.count(b[i])) {
      mb[b[i]].push_back(i);
    } else {
      mb[b[i]] = {i};
    }
  }
  sort(ALL(coords));
  coords.resize(unique(ALL(coords)) - coords.begin());
  reverse(ALL(coords));
  vec<int> ans(n + 1);
  for (int x : coords) {
    if (ma.count(x)) {
      for (auto i : ma[x]) {
        add(0, 0, n + 1, i + 1, n + 1);
      }
    }
    if (mb.count(x)) {
      for (auto i : mb[x]) {
        add(0, 0, n + 1, 0, i + 1);
      }
    }
    ans[(t[0] - 1)] = max(ans[(t[0] - 1)], x);
  }
  for (int i = n - 1; i >= 0; i--) {
    ans[i] = max(ans[i + 1], ans[i]);
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
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



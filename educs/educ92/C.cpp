//
// Created by watemus on 29.07.2020.
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
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 2e5 + 10;

int t[MAXN * 4];

void build(int v, int lb, int rb) {
  if (rb - lb == 1) {
    t[v] = 0;
  } else {
    int mid = (lb + rb) / 2;
    build(v * 2 + 1, lb, mid);
    build(v * 2 + 2, mid, rb);
    t[v] = 0;
  }
}

void modify(int v, int lb, int rb, int at, int val) {
  if (rb - lb == 1) {
    t[v] = val;
  } else {
    int mid = (lb + rb) / 2;
    if (at < mid) {
      modify(v * 2 + 1, lb, mid, at, val);
    } else {
      modify(v * 2 + 2, mid, rb, at, val);
    }
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
  }
}

int get(int v, int lb, int rb, int lq, int rq) {
  if (lq <= lb && rb <= rq) {
    return t[v];
  }
  int ans = 0;
  int mid = (lb + rb) / 2;
  if (lq < mid) {
    ans = max(ans, get(v * 2 + 1, lb, mid, lq, rq));
  }
  if (mid < rq){
    ans = max(ans, get(v * 2 + 2, mid, rb, lq, rq));
  }
  return ans;
}

void run() {
  string s;
  cin >> s;
  int n = s.size();
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    char ch = s[i];
    a[i] = ch - '0';
  }
  int ans = 0;
  for (int mask = 0; mask < 100; mask++) {
    int cans = 0;
    int i = 0;
    int a0 = mask / 10, a1 = mask % 10;
    while (i < n) {
      int j = i;
      for (; j < n && a[j] != a0; j++);
      if (j < n && a1 == a0) cans++;
      j++;
      for (; j < n && a[j] != a1; j++);
      if (j < n && a0 == a1) cans++;
      if (j < n && a0 != a1) cans+=2;
      i = j + 1;
    }
    if (cans> ans) {
      ans = cans;
    }
  }
  cout << n - ans << "\n";
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



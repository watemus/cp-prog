//
// Created by watemus on 22.11.2020.
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


const int N = 12;

int n;
ld x[N], y[N], r[N];

const ld EPS = 1e-6;

ld dist(ld x1, ld y1, ld x2, ld y2) {
  return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool check(ld xx, ld yy) {
  for (int i = 0; i < n; i++) {
    ld cdist = dist(xx, yy, x[i], y[i]);
    ld cr = r[i];
    if (cdist < cr) {
      return false;
    }
  }
  return true;
}

ld X, Y;

bool rec(ld x1, ld x2, ld y1, ld y2, ld R) {
  if (x2 - x1 < EPS || y2 - y1 < EPS || x2 < R || y2 < R || (X - x1) < R || (Y - y1) < R) {
    return false;
  }
  for (int i = 0; i < n; i++) {
    if (dist(x1, y1, x[i], y[i]) < r[i] && dist(x1, y2, x[i], y[i]) < r[i] &&
        dist(x2, y1, x[i], y[i]) < r[i] && dist(x2, y2, x[i], y[i]) < r[i]) {
      return false;
    }
  }
  if (x1 > R && y1 > R && (X - x1) > R && (Y - y1) > R && check(x1, y1)) {
    return true;
  }
  if (x1 > R && y2 > R && (X - x1) > R && (Y - y2) > R && check(x1, y2)) {
    return true;
  }
  if (x2 > R && y1 > R && (X - x2) > R && (Y - y1) > R && check(x2, y1)) {
    return true;
  }
  if (x2 > R && y2 > R && (X - x2) > R && (Y - y2) > R && check(x2, y2)) {
    return true;
  }
  ld cc1 = (ld(rnd()) / UINT32_MAX);
  ld cc2 = (ld(rnd()) / UINT32_MAX);
  ld mx = x1 + (x2 - x1) * (cc1);
  ld my = y1 + (y2 - y1) * (cc2);
  vec<tuple<ld, ld, ld, ld>> v;
  v.emplace_back(x1, mx, y1, my);
  v.emplace_back(x1, mx, my, y2);
  v.emplace_back(mx, x2, y1, my);
  v.emplace_back(mx, x2, my, y2);
  shuffle(ALL(v), rnd);
  for (int i = 0; i < 4; i++) {
    bool cr = rec(get<0>(v[i]), get<1>(v[i]), get<2>(v[i]), get<3>(v[i]), R);
    if (cr)
      return true;
  }
  return false;
}

void run() {
  cin >> X >> Y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i] >> r[i];
  }
  ld LL = 0;
  ld RR = min(X, Y) / 2;
  while ((RR - LL) > EPS) {
    ld mid = (LL + RR) / 2;
    for (int i = 0; i < n; i++) {
      r[i] += mid;
    }
    bool cr = rec(0, X, 0, Y, mid);
    if (cr) {
      LL = mid;
    } else {
      RR = mid;
    }
    for (int i = 0; i < n; i++) {
      r[i] -= mid;
    }
  }
  cout << LL << endl;
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



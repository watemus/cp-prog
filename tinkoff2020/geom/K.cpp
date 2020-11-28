//
// Created by watemus on 25.11.2020.
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

constexpr ld EPS = 1e-10;

struct Pt {
  ld x, y;
};

Pt operator+(Pt a, Pt b) {
  return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

Pt operator*(Pt a, ld k) {
  return {a.x * k, a.y * k};
}

Pt operator/(Pt a, ld k) {
  return {a.x / k, a.y / k};
}

ld operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

ld operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

ld len(Pt a) {
  return sqrt(a % a);
}

Pt set_len(Pt a, ld ln) {
  ld clen = len(a);
  a = a / clen * ln;
  return a;
}

Pt rotate90(Pt a) {
  return {-a.y, a.x};
}

struct Half_plane {
  ld a, b, c;
  bool in(Pt p) {
    return a * p.x + b * p.y + c > -EPS;
  }
  Half_plane(Pt p, Pt q) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -a * p.x - b * p.y;
    auto vc = rotate90(q - p);
    if (!in(p + vc)) {
      a *= -1;
      b *= -1;
      c *= -1;
    }
  }
};

int n, m;

vec<Pt> a, b;



bool solve(ld r) {
  vec<Half_plane> na;
  for (int i = 1; i <= a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      auto p = a[i - 1] - b[j];
      auto q = a[i % n] - b[j];
      auto pq = q - p;
      auto sh = set_len(rotate90(pq), r * 2);
      na.emplace_back(p + sh, q + sh);
    }
  }
}

void run() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  cin >> m;
  b.resize(m);
  for (int i = 0; i < m; i++) {
    cin >> b[i].x >> b[i].y;
  }
  ld l = 0;
  ld r = 2000;
  for (int iters = 0; iters < 100; iters++) {
    ld mid = (l + r) / 2;
    if (solve(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << fixed << setprecision(20);
  cout << l << '\n';
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



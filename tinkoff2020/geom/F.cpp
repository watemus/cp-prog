//
// Created by watemus on 23.11.2020.
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

constexpr ld EPS = 1e-7;

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

ld operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

ld operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

Pt rotate90(Pt a) {
  return {-a.y, a.x};
}

ld dist(Pt a, Pt b) {
  return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct Line {
  ld a, b, c;
  Line(Pt p, Pt q) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -(a * p.x) - (b * p.y);
  }
};

Pt inter(Line l1, Line l2) {
  ld den = l1.a * l2.b - l2.a * l1.b;
  ld x = -(l1.c * l2.b - l2.c * l1.b) / den;
  ld y = -(l1.a * l2.c - l2.a * l1.c) / den;
  return Pt{x, y};
}

struct Cir {
  Pt c;
  ld r;
};

Cir make_circle(Pt a, Pt b, Pt c) {
  if ((c - a) % (b - a) < EPS) {
    return {(c + b) * 0.5, dist(c, b) / 2};
  }
  if ((a - b) % (c - b) < EPS) {
    return {(a + c) * 0.5, dist(c, a) / 2};
  }
  if ((a - c) % (b - c) < EPS) {
    return {(a + b) * 0.5, dist(a, b) / 2};
  }
  Pt m1 = (a + b) * 0.5;
  Pt m2 = (a + c) * 0.5;
  Pt v1 = rotate90(b - a);
  Pt v2 = rotate90(c - a);
  Line l1(m1, m1 + v1);
  Line l2(m2, m2 + v2);
  Pt cc = inter(l1, l2);
  return {cc, dist(cc, a)};
}

bool in(Cir c, Pt a) {
  return dist(c.c, a) <= c.r + EPS;
}

Cir build3(vec<Pt> &p, Pt a, Pt b, int l) {
  Cir cr = make_circle(a, b, p[0]);
  for (int i = 1; i <= l; i++) {
    if (!in(cr, p[i])) {
      cr = make_circle(a, b, p[i]);
    }
  }
  return cr;
}

Cir build2(vec<Pt> &p, Pt a, int l) {
  Cir cr = make_circle(a, p[0], p[0]);
  for (int i = 1; i <= l; i++) {
    if (!in(cr, p[i])) {
      cr = build3(p, a, p[i], l);
    }
  }
  return cr;
}

Cir build1(vec<Pt> &p) {
  shuffle(ALL(p), rnd);
  Cir cr = make_circle(p[0], p[0], p[0]);
  for (int i = 1; i < p.size(); i++) {
    if (!in(cr, p[i])) {
      cr = build2(p, p[i], i);
    }
  }
  return cr;
}

void run() {
  int n;
  cin >> n;
  vec<Pt> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
  }
  Cir res = build1(p);
  cout << fixed << setprecision(7);
  cout << res.c.x << ' ' << res.c.y << endl;
  cout << res.r << endl;
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



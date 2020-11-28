//
// Created by watemus on 21.11.2020.
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

ld EPS = 1e-18;

struct Pt {
  ld x, y;
};

Pt operator+(Pt a, Pt b) {
  return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

Pt operator-(Pt a) {
  return {-a.x, -a.y};
}

Pt operator*(Pt a, int k) {
  a.x *= k;
  a.y *= k;
  return a;
}

ld operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

ld operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

ld dist(Pt a, Pt b) {
  return sqrtl((a - b).x * (a - b).x + (a - b).y * (a - b).y);
}

struct Seg {
  Pt a, b;
};

struct Ray {
  Pt a, b;
};

struct Line {
  ld a, b, c;
  Line(Pt p, Pt q) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -(a * p.x) - (b * p.y);
    if (a < 0 || fabsl(a) < EPS && b < 0) {
      a *= -1;
      b *= -1;
      c *= -1;
    }
    ld d = sqrtl(a * a + b * b);
    a /= d;
    b /= d;
    c /= d;
  }
  explicit Line(Seg s) : Line(s.a, s.b) {}
  explicit Line(Ray r) : Line(r.a, r.b) {}
};

bool parallel(Line l1, Line l2) {
  return fabsl(l1.a * l2.b - l2.a * l1.b) < EPS;
}

optional<Pt> inter(Line l1, Line l2) {
  if (parallel(l1, l2)) {
    return {};
  }
  ld den = l1.a * l2.b - l2.a * l1.b;
  ld x = -(l1.c * l2.b - l2.c * l1.b) / den;
  ld y = -(l1.a * l2.c - l2.a * l1.c) / den;
  return Pt{x, y};
}

int sign(int a) {
  if (a == 0) {
    return 0;
  }
  return a / abs(a);
}

bool check_ray(Ray r, Pt a) {
  auto v1 = (a - r.a);
  auto v2 = (r.b - r.a);
  ld prod = (a - r.a) % (r.b - r.a);
  return prod >= -EPS;
}

bool check_seg(Seg s, Pt a) {
  return check_ray({s.a, s.b}, a) && check_ray({s.b, s.a}, a);
}

ld dist(Pt a, Line l) {
  return fabsl(l.a * a.x + l.b * a.y + l.c) / sqrtl(l.a * l.a + l.b * l.b);
}

ld dist(Pt a, Seg s) {
  ld ans = min(dist(a, s.a), dist(a, s.b));
  if (check_seg(s, a)) {
    ans = min(ans, dist(a, Line(s)));
  }
  return ans;
}

ld dist(Pt a, Ray r) {
  ld ans = dist(a, r.a);
  if (check_ray(r, a)) {
    ans = min(ans, dist(a, Line(r)));
  }
  return ans;
}

ld dist(Seg s, Seg t) {
  auto p = inter(Line(s), Line(t));
  if (p.has_value() && check_seg(s, p.value()) && check_seg(t, p.value())) {
    return 0;
  }
  return min({dist(s.a, t), dist(s.b, t), dist(t.a, s), dist(t.b, s)});
}

ld dist(Seg s, Ray t) {
  auto p = inter(Line(s), Line(t));
  if (p.has_value() && check_seg(s, p.value()) && check_ray(t, p.value())) {
    return 0;
  }
  return min({dist(s.a, t), dist(s.b, t), dist(t.a, s), dist(t.b, s)});
}

ld dist(Ray s, Ray t) {
  auto p = inter(Line(s), Line(t));
  if (p.has_value() && check_ray(s, p.value()) && check_ray(t, p.value())) {
    return 0;
  }
  return min({dist(s.a, t), dist(s.b, t), dist(t.a, s), dist(t.b, s)});
}

ld dist(Line l1, Line l2) {
  if (parallel(l1, l2)) {
    ld d1 = sqrtl(l1.a * l1.a + l1.b * l1.b);
    ld d2 = sqrtl(l2.a * l2.a + l2.b * l2.b);
    l1.a /= d1;
    l1.b /= d1;
    l1.c /= d1;
    l2.a /= d2;
    l2.b /= d2;
    l2.c /= d2;
    return fabsl(l1.c - l2.c);
  }
  return 0;
}

ld dist(Line l, Seg s) {
  Line l1 = l;
  Line l2(s);
  if (parallel(l1, l2)) {
    ld d1 = sqrtl(l1.a * l1.a + l1.b * l1.b);
    ld d2 = sqrtl(l2.a * l2.a + l2.b * l2.b);
    l1.a /= d1;
    l1.b /= d1;
    l1.c /= d1;
    l2.a /= d2;
    l2.b /= d2;
    l2.c /= d2;
    return fabsl(l1.c - l2.c);
  }
  auto p = inter(l1, l2);
  if (check_seg(s, p.value())) {
    return 0;
  }
  return min(dist(s.a, l), dist(s.b, l));
}

ld dist(Line l, Ray s) {
  Line l1 = l;
  Line l2(s);
  if (parallel(l1, l2)) {
    ld d1 = sqrtl(l1.a * l1.a + l1.b * l1.b);
    ld d2 = sqrtl(l2.a * l2.a + l2.b * l2.b);
    l1.a /= d1;
    l1.b /= d1;
    l1.c /= d1;
    l2.a /= d2;
    l2.b /= d2;
    l2.c /= d2;
    return fabsl(l1.c - l2.c) / d1;
  }
  auto p = inter(l1, l2);
  if (check_ray(s, p.value())) {
    return 0;
  }
  return min(dist(s.a, l), dist(s.b, l));
}

void run() {
  Pt a, b, c, d;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
  cout << fixed << setprecision(6);
  cout << dist(a, c) << '\n';
  cout << dist(a, Seg{c, d}) << '\n';
  cout << dist(a, Ray{c, d}) << '\n';
  cout << dist(a, Line(c, d)) << '\n';
  cout << dist(c, Seg{a, b}) << '\n';
  cout << dist(Seg{a, b}, Seg{c, d}) << '\n';
  cout << dist(Seg{a, b}, Ray{c, d}) << '\n';
  cout << dist(Line(c, d), Seg{a, b}) << '\n';
  cout << dist(c, Ray{a, b}) << '\n';
  cout << dist(Seg{c, d}, Ray{a, b}) << '\n';
  cout << dist(Ray{c, d}, Ray{a, b}) << '\n';
  cout << dist(Line(c, d), Ray{a, b}) << '\n';
  cout << dist(c, Line(a, b)) << '\n';
  cout << dist(Line(a, b), Seg{c, d}) << '\n';
  cout << dist(Line(a, b), Ray{c, d}) << '\n';
  cout << dist(Line(c, d), Line(a, b)) << '\n';
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



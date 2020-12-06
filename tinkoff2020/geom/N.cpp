//
// Created by watemus on 30.11.2020.
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

constexpr ld EPS = 1e-6;

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
  Pt m1 = (a + b) * 0.5;
  Pt m2 = (a + c) * 0.5;
  Pt v1 = rotate90(b - a);
  Pt v2 = rotate90(c - a);
  Line l1(m1, m1 + v1);
  Line l2(m2, m2 + v2);
  Pt cc = inter(l1, l2);
  return {cc, dist(cc, a)};
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<pair<int, int>> pts(n);
  for (int i = 0; i < n; i++) {
    cin >> pts[i].first >> pts[i].second;
  }
  map<pair<pair<int, int>, pair<int, int>>, vec<pair<int, int>>> mp;
  for (int i = 0; i < m; i++) {
    int i1, i2, i3;
    cin >> i1 >> i2 >> i3;
    i1--, i2--, i3--;
    mp[{pts[i1], pts[i2]}].push_back(pts[i3]);
    mp[{pts[i2], pts[i1]}].push_back(pts[i3]);
    mp[{pts[i1], pts[i3]}].push_back(pts[i2]);
    mp[{pts[i3], pts[i1]}].push_back(pts[i2]);
    mp[{pts[i2], pts[i3]}].push_back(pts[i1]);
    mp[{pts[i3], pts[i2]}].push_back(pts[i1]);
  }
  bool ans = true;
  for (auto &[pp, vc] : mp) {
    if (vc.size() == 1)
      continue;
    auto [pr1, pr2] = pp;
    Pt p1 {(ld)pr1.first, (ld)pr1.second};
    Pt p2 {(ld)pr2.first, (ld)pr2.second};
    Pt p3 {(ld)vc[0].first, (ld)vc[0].second};
    Pt p4 {(ld)vc[1].first, (ld)vc[1].second};
    auto c1 = make_circle(p1, p2, p3);
    if (dist(c1.c, p4) < c1.r - EPS) {
      ans = false;
//      break;
    }
    auto c2 = make_circle(p1, p2, p4);
    if (dist(c2.c, p3) < c2.r - EPS) {
      ans = false;
//      break;
    }
  }
  cout << (ans ? "YES\n" : "NO\n");
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



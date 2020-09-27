//
// Created by watemus on 21.08.2020.
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

struct Pt {
  int x, y;
};

int operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

int operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

Pt operator+(Pt a, Pt b) {
  return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

Pt operator-(Pt a) {
  return {-a.x, -a.y};
}

bool operator<(Pt a, Pt b) {
  return a * b > 0;
}

bool operator>(Pt a, Pt b) {
  return a * b < 0;
}

bool operator<=(Pt a, Pt b) {
  return a * b >= 0;
}

bool operator>=(Pt a, Pt b) {
  return a * b <= 0;
}

bool operator==(Pt a, Pt b) {
  return a.x == b.x && b.y == a.y;
}

void run() {
  int n;
  cin >> n;
  vec<Pt> poly(n);
  Pt cd {0, 0};
  cin >> cd.x >> cd.y;
  for (auto &[x, y] : poly) {
    cin >> x >> y;
    //x *= n, y *= n;
  }
  Pt mn = *min_element(ALL(poly), [](Pt a, Pt b){
    return tie(a.x, a.y) < tie(b.x, b.y);
  });
  for(auto &pt : poly) {
    pt = pt - mn;
  }
  cd = cd - mn;
  poly.erase(find(ALL(poly), Pt{0, 0}));
  sort(ALL(poly), [](Pt a, Pt b){
    return a < b;
  });
  vec<Pt> convex_hull {{0, 0}, poly[0]};
  for (int i = 1; i < poly.size(); i++) {
    while (convex_hull.size() > 1) {
      Pt p1 = poly[i];
      Pt p2 = convex_hull[convex_hull.size() - 1];
      Pt p3 = convex_hull[convex_hull.size() - 2];
      Pt v1 = p1 - p2;
      Pt v2 = p2 - p3;
      if (v2 * v1 <= 0) {
        convex_hull.pop_back();
      } else {
        break;
      }
    }
    convex_hull.push_back(poly[i]);
  }
  int ans = 0;
  for (int i = 0; i < convex_hull.size(); i++) {
    Pt p1 = convex_hull[i];
    Pt p2 = convex_hull[(i + 1) % convex_hull.size()];
    auto p1_p2 = p2 - p1;
    auto p2_p1 = p1 - p2;
    auto p1_cd = cd - p1;
    auto p2_cd = cd - p2;
    if (p1_p2 % p1_cd > 0 && p2_p1 % p2_cd > 0) ans++;
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



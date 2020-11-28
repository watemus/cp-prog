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

struct Pt {
  int x, y;
};

int operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

Pt operator+(Pt a, Pt b) {
  return {a.x + b.x, a.y + b.y};
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

Pt operator,(Pt a, Pt b) {
  return b - a;
}

bool check_tr(Pt a, Pt b, Pt c, Pt p) {
  return (a, p) >= (a, b) && (b, p) >= (b, c) && (c, p) >= (c, a);
}

void run() {
  int n, k, m;
  cin >> n >> m >> k;
  vec<Pt> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  vec<Pt> s(n - 1);
  for (int i = 0; i < n - 1; i++) {
    s[i] = (a[0], a[i + 1]);
  }
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    Pt cr {0, 0};
    cin >> cr.x >> cr.y;
    cr = (a[0], cr);
    if (s[0] <= cr && cr <= s.back()) {
      int j = lower_bound(s.begin() + 1, s.end() - 1, cr) - s.begin();
      if (check_tr({0, 0}, s[j - 1], s[j], cr))
        cnt++;
    }
  }
  if (cnt >= k) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
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



//
// Created by watemus on 18.10.2020.
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

struct Pt {
  int x, y;
};

int operator*(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

pair<int, int> tt(Pt a) {
  return {a.x, a.y};
}

void run() {
  int n;
  cin >> n;
  vec<Pt> a(n);
  map<pair<int, int>, int> cnt;
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
    if (a[i].y < 0 || (a[i].y == 0 && a[i].x < 0)) {
      a[i].x *= -1;
      a[i].y *= -1;
    }
    cnt[{a[i].x, a[i].y}]++;
  }
  int ans = 0;
  set<pair<pair<int, int>, pair<int, int>>> usd;
  for (int i = 0; i < n; i++) {
    Pt b = {-a[i].y, a[i].x};
    if (b.y < 0 || (b.y == 0 && b.x < 0)) {
      b.x *= -1;
      b.y *= -1;
    }
    ans += (cnt[tt(a[i])] - 1) * (cnt[tt(b)] * (cnt[tt(b)] - 1)) * 4;
    cnt[tt(a[i])]--;
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



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

#define int __int128

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

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

int operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

int operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

void run() {
  ll n;
  cin >> n;
  vec<Pt> a(n);
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    tie(a[i].x, a[i].y) = tuple(x, y);
    a[i].y -= a[i].x * a[i].x;
  }
  int f = min_element(ALL(a), [](Pt a, Pt b){
    return tuple(a.x, a.y) < tuple(b.x, b.y);
  }) - a.begin();
  swap(a[0], a[f]);
  Pt pp = a[0];
  sort(a.begin() + 1, a.end(), [pp](Pt a, Pt b){
    if ((a - pp) * (b - pp) == 0) {
      return (a - pp) % (a - pp) < (b - pp) % (b - pp);
    }
    return ((a - pp) * (b - pp)) > 0;
  });
  vec<Pt> st {a[0]};
  for (int i = 1; i < a.size(); i++) {
    if (st.size() > 1) {
      while (st.size() > 1 && (a[i] - st.back()) * (st[st.size() - 2] - st.back()) <= 0) {
        st.pop_back();
      }
    }
    st.push_back(a[i]);
  }
  ll ans = 0;
  for (int i = 1; i <= st.size(); i++) {
    ans += bool((st[i % st.size()] - (st[i - 1])) % Pt{-1, 0} > 0);
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



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

void run() {
  int n;
  cin >> n;
  vec<Pt> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  vec<int> ans;
  vec<int> usd(n);
  int cr = min_element(ALL(a), [](Pt a, Pt b){
    return tuple(a.x, a.y) < tuple(b.x, b.y);
  }) - a.begin();
  ans.push_back(cr);
  usd[cr] = 1;
  string s;
  cin >> s;
  for (int i = 0; i < n - 2; i++) {
    cr = -1;
    for (int j = 0; j < n; j++) {
      if (s[i] == 'R') {
        if (!usd[j] && (cr == -1 || (a[cr] - a[ans[i]]) * (a[j] - a[ans[i]]) > 0)) {
          cr = j;
        }
      } else {
        if (!usd[j] && (cr == -1 || (a[cr] - a[ans[i]]) * (a[j] - a[ans[i]]) < 0)) {
          cr = j;
        }
      }
    }
    ans.push_back(cr);
    usd[cr] = 1;
  }
  for (int i = 0; i < n; i++) {
    if (!usd[i]) {
      ans.push_back(i);
    }
  }
  for (auto el : ans) {
    cout << el + 1 << ' ';
  }
  cout << '\n';
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



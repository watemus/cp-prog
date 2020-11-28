//
// Created by watemus on 24.11.2020.
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

#define int short

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
  signed x, y;
};

Pt operator+(Pt a, Pt b) {
  return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
  return {a.x - b.x, a.y - b.y};
}

ll operator*(Pt a, Pt b) {
  return a.x * 1ll * b.y - a.y * 1ll* b.x;
}

ll operator%(Pt a, Pt b) {
  return a.x * b.x + a.y + b.y;
}

bool operator<(Pt a, Pt b) {
  return a * b > 0;
}

bool operator==(Pt a, Pt b) {
  return a.x == b.x && a.y == b.y;
}

bool operator!=(Pt a, Pt b) {
  return !(a == b);
}

vec<pair<int, Pt>> st;

void convex_hull(vec<pair<int, Pt>> &p, bool ss) {
  if (ss) {
    int f = min_element(ALL(p), [](pair<int, Pt> a, pair<int, Pt> b){
      return make_tuple(a.second.x, a.second.y) < make_tuple(b.second.x, b.second.y);
    }) - p.begin();
    swap(p[f], p[0]);
    Pt pf = p[0].second;
    sort(p.begin() + 1, p.end(), [pf](pair<int, Pt> a, pair<int, Pt> b){
      return (a.second - pf) < (b.second - pf);
    });
  }
  st.clear();
  st.push_back(p[0]);
  for (int i = 1; i < p.size(); i++) {
    while (st.size() > 1 && (p[i].second - st.back().second) < (st.back().second - st[st.size() - 2].second)) {
      st.pop_back();
    }
    st.push_back(p[i]);
  }
}

bool ask(vec<int> &p) {
  printf("? %d ", p.size());
  for (auto el : p) {
    printf("")
  }
  cout << endl;
  string res;
  cin >> res;
  return res == "Yes";
}

void run() {
  int n;
  cin >> n;
  vec<pair<int, Pt>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].second.x >> p[i].second.y;
    p[i].first = i;
  }
  int q;
  cin >> q;
  vec<pair<int, Pt>> cr;
  vec<int> ids;
  while (q--) {
    int f = min_element(ALL(p), [](pair<int, Pt> a, pair<int, Pt> b) {
      return make_tuple(a.second.x, a.second.y) < make_tuple(b.second.x, b.second.y);
    }) - p.begin();
    swap(p[f], p[0]);
    Pt pf = p[0].second;
    sort(p.begin() + 1, p.end(), [pf](pair<int, Pt> a, pair<int, Pt> b) {
      return (a.second - pf) < (b.second - pf);
    });
    int l = 2;
    int r = n;
    while (l + 1 < r) {
      int mid = (l + r) / 2;
      cr.clear();
      for (int i = l - 2; i < mid; i++) {
        cr.push_back(p[i]);
      }
      convex_hull(cr, false);
      cr.resize(st.size());
      copy(ALL(st), cr.begin());
      ids.clear();
      for (auto ccc : cr) {
        ids.push_back(ccc.first);
      }
      bool res = ask(ids);
      if (res) {
        r = mid;
      } else {
        l = mid;
      }
    }
    auto c = p[l];
    vec<pair<int, Pt>> oth{p[0]};
    {
      for (int i = l - 2; i < l; i++) {
        cr.push_back(p[i]);
      }
      convex_hull(cr, false);
      cr.resize(st.size());
      copy(ALL(st), cr.begin());
      while (cr.size() > 1 && (p[l].second - cr.back().second) < (cr.back().second - cr[cr.size() - 2].second)) {
        oth.push_back(cr.back());
        cr.pop_back();
      }
      if (cr.back() != oth[0]) {
        oth.push_back(cr.back());
      }
      cr.push_back(p[l]);
    }
    l = 1;
    r = oth.size();
    while (l + 1 < r) {
      int mid = (l + r) / 2;
      cr.clear();
      cr.push_back(c);
      for (int i = 0; i < mid; i++) {
        cr.push_back(oth[i]);
      }
      convex_hull(cr, false);
      cr.resize(st.size());
      copy(ALL(st), cr.begin());
      ids.clear();
      for (auto ccc : cr) {
        ids.push_back(ccc.first);
      }
      bool res = ask(ids);
      if (res) {
        r = mid;
      } else {
        l = mid;
      }
    }
    cout << "! 3 " << c.first + 1 << ' ' << oth[l - 1].first + 1 << " " << oth[l].first + 1 << endl;
  }
}

signed main() {
#ifdef LOCAL
//  std::freopen("input.txt", "r", stdin);
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
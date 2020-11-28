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

struct Pt {
  ld x, y;
};

ld dist(Pt a, Pt b) {
  return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

const int N = 3000;
constexpr ld EPS = 1e-6;

int pr[N], sz[N];

int get(int u) {
  if (pr[u] == -1)
    return u;
  return pr[u] = get(pr[u]);
}

void unite(int u, int v) {
  u = get(u);
  v = get(v);
  if (u == v)
    return;
  if (sz[u] < sz[v])
    swap(u, v);
  pr[v] = u;
  sz[u] += sz[v];
}

void run() {
  int n, m;
  cin >> n >> m;
  ld w, h;
  cin >> w >> h;
  vec<Pt> a(n);
  vec<ld> rs(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i].x >> a[i].y >> rs[i];
  }
  vec<pair<ld, pair<int, int>>> tt;
  int up = n;
  int down = n + 1;
  int left = n + 2;
  int right = n + 3;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      tt.emplace_back(dist(a[i], a[j]) - rs[i] - rs[j], pair{i, j});
    }
    tt.emplace_back(a[i].x - rs[i], pair{i, left});
    tt.emplace_back(w - a[i].x - rs[i], pair{i, right});
    tt.emplace_back(a[i].y - rs[i], pair{i, down});
    tt.emplace_back(h - a[i].y - rs[i], pair{i, up});
  }
  tt.emplace_back(w, pair(left, right));
  tt.emplace_back(h, pair(up, down));
  vec<pair<ld, int>> qs(m);
  vec<int> en(m);
  for (int i = 0; i < m; i++) {
    cin >> qs[i].first;
    qs[i].second = i;
    cin >> en[i];
  }
  vec<string> ans(m);
  sort(ALL(qs));
  memset(pr, -1, sizeof pr);
  fill(sz, sz + N, 1);
  int j = 0;
  sort(ALL(tt));
  for (auto [r, id] : qs) {
    while (j < tt.size() && tt[j].first < r * 2) {
      unite(tt[j].second.first, tt[j].second.second);
      j++;
    }
    int cen = en[id];
    string ansik = to_string(en[id]);

    if (cen == 1) {
      if (get(left) != get(down)) {
        if (get(up) != get(down) && get(right) != get(down)) {
          ansik += '2';
        }
        if (get(left) != get(up) && get(left) != get(right)) {
          ansik += '4';
        }
        if (get(up) != get(down) && get(left) != get(right) && get(up) != get(right)) {
          ansik += '3';
        }
      }
    } else if (cen == 2) {
      if (get(right) != get(down)) {
        if (get(up) != get(down) && get(left) != get(down)) {
          ansik += '1';
        }
        if (get(left) != get(right) && get(right) != get(up)) {
          ansik += '3';
        }
        if (get(up) != get(down) && get(left) != get(right) && get(up) != get(left)) {
          ansik += '4';
        }
      }
    } else if (cen == 3) {
      if (get(up) != get(right)) {
        if (get(right) != get(down) && get(left) != get(right)) {
          ansik += '2';
        }
        if (get(up) != get(down) && get(up) != get(left)) {
          ansik += '4';
        }
        if (get(up) != get(down) && get(left) != get(right) && get(left) != get(down)) {
          ansik += '1';
        }
      }
    } else {
      if (get(up) != get(left)) {
        if (get(up) != get(down) && get(up) != get(right)) {
          ansik += '3';
        }
        if (get(left) != get(right) && get(left) != get(down)) {
          ansik += '1';
        }
        if (get(up) != get(down) && get(left) != get(right) && get(down) != get(right)) {
          ansik += '2';
        }
      }
    }
    ans[id] = ansik;
  }
  for (int i = 0; i < m; i++) {
    sort(ALL(ans[i]));
    cout << ans[i] << '\n';
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



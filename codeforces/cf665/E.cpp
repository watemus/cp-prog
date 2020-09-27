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

struct Event {
  bool vert;
  //Vert
  int ly;
  int ry;
  int x;
  //Hor
  int at;
  int y;
  bool beg;
};

Event make_ver(int ly, int ry, int x) {
  return {true, ly, ry, x, 0, 0, false};
}

Event make_hor(int at, int y, bool beg) {
  return {false, 0, 0, 0, at, y, beg};
}

const int MAX = 1e6;

int t[(MAX + 228) * 4 + 228];

void modify(int v, int lb, int rb, int at, int dt) {
  if (rb - lb == 1) {
    t[v] += dt;
  } else {
    int mid = (lb + rb) / 2;
    if (at < mid) {
      modify(v * 2 + 1, lb, mid, at, dt);
    } else {
      modify(v * 2 + 2, mid, rb, at, dt);
    }
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
  }
}

int get(int v, int lb, int rb, int lq, int rq) {
  if (lq <= lb && rb <= rq) {
    return t[v];
  } else {
    int ans = 0;
    int mid = (lb + rb) / 2;
    if (lq < mid) {
      ans += get(v * 2 + 1, lb, mid, lq, rq);
    }
    if (mid < rq) {
      ans += get(v * 2 + 2, mid, rb, lq, rq);
    }
    return ans;
  }
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<Event> sweep_line;
  for (int i = 0; i < n; i++) {
    int y, lx, rx;
    cin >> y >> lx >> rx;
    if (y == 0 || y == MAX)
      continue;
    sweep_line.push_back(make_hor(lx, y, true));
    sweep_line.push_back(make_hor(rx, y, false));
  }
  sweep_line.push_back(make_hor(0, 0, true));
  sweep_line.push_back(make_hor(MAX, 0, false));
  sweep_line.push_back(make_hor(0, MAX, true));
  sweep_line.push_back(make_hor(MAX, MAX, false));
  for (int i = 0; i < m; i++) {
    int x, ly, ry;
    cin >> x >> ly >> ry;
    if (x == 0 || x == MAX)
      continue;
    sweep_line.push_back(make_ver(ly, ry, x));
  }
  sweep_line.push_back(make_ver(0, MAX, 0));
  sweep_line.push_back(make_ver(0, MAX, MAX));
  sort(ALL(sweep_line), [](const Event &a, const Event &b){
    if (a.vert && b.vert) {
      return a.x < b.x;
    }
    else if (!a.vert && !b.vert) {
      if (a.at == b.at) {
        return a.beg > b.beg;
      }
      return a.at < b.at;
    }
    else if (a.vert && !b.vert) {
      if (a.x == b.at) {
        return !b.beg;
      } else {
        return a.x < b.at;
      }
    }
    else {
      if (a.at == b.x) {
        return a.beg;
      } else {
        return a.at < b.x;
      }
    }
  });
  int nodes = (n + m) * 2 + 8, edges = nodes / 2;
  memset(t, 0, sizeof t);
  for (auto event : sweep_line) {
    if (event.vert) {
      int cs = get(0, 0, MAX + 1, event.ly, event.ry + 1);
      nodes += cs;
      edges += cs * 2;
    } else {
      if (event.beg) {
        modify(0, 0, MAX + 1, event.y, 1);
      } else {
        modify(0, 0, MAX + 1, event.y, -1);
      }
    }
  }
  cout << 1 + edges - nodes << '\n';
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



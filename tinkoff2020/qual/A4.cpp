//
// Created by watemus on 01.09.2020.
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

vec<pair<int, int>> DD = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

int ex_gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int px, py;
  int d = ex_gcd(b, a % b, px, py);
  x = py;
  y = px - a / b * py;
  return d;
}

optional<pair<int, int>> diophant(int a, int b, int c) {
  if (c < 0) {
    a *= -1;
    b *= -1;
    c *= -1;
  }
  int x, y;
  int g = ex_gcd(a, b, x, y);
  if (c % g)
    return {};
  x *= c / g;
  y *= c / g;
  if (x < 0) {
    int k = (abs(x) / (b / g));
    x += k * (b / g);
    y -= k * (a / g);
    if (x < 0) {
      x += (b / g);
      y -= (a / g);
    }
  } else {
    int k = (x / (b / g));
    x -= k * (b / g);
    y += k * (a / g);
  }
  return pair{x, y};
}

optional<int> solve_crt(int a1, int n1, int a2, int n2) {
  auto sol = diophant(n1, -n2, a2 - a1);
  if (!sol.has_value())
    return {};
  int x = a1 + sol->first * n1;
  int n = lcm(n1, n2);
  if (x < 0) {
    x += (abs(x) / n) * n;
    if (x < 0)
      x += n;
  }
  if (x > n) {
    x %= n;
  }
  return x;
}

void run() {
  int n, m, k;
  cin >> n >> m >> k;
  //assert(n < 10 && m < 10);
  int fin_x, fin_y;
  cin >> fin_x >> fin_y;
  vec<tuple<int, int, int>> robots(k);
  auto rotates = Vec(k, n + 2, m + 2, 0);
  auto free = Vec(n + 2, m + 2, 0);
  for (int h = 0; h < k; h++) {
    auto to_vec = [](char ch) {
      if (ch == 'U') return 0;
      else if (ch == 'R') return 1;
      else if (ch == 'D') return 2;
      else return 3;
    };
    {
      int x, y, r;
      cin >> x >> y;
      char rot;
      cin >> rot;
      r = to_vec(rot);
      robots[h] = {x, y, r};
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char ch;
        cin >> ch;
        rotates[h][i][j] = ch - '0';
        free[i][j] = 1;
      }
    }
  }
  auto id = Vec(n + 2, m + 2, 4, 0);
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int h = 0; h < 4; h++) {
        id[i][j][h] = cnt++;
      }
    }
  }
  auto go = Vec(k, cnt, 0);
  for (int g = 0; g < k; g++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        for (int h = 0; h < 4; h++) {
          int nh = (h + rotates[g][i][j]) % 4;
          int ni = i + DD[nh].first;
          int nj = j + DD[nh].second;
          if (!free[ni][nj]) {
            nh = (nh + 2) % 4;
            ni = i + DD[nh].first;
            nj = j + DD[nh].second;
          }
          go[g][id[i][j][h]] = id[ni][nj][nh];
        }
      }
    }
  }
  set<int> fins;
  for (int i = 0; i < 4; i++) {
    fins.insert(id[fin_x][fin_y][i]);
  }
  vec<int> robots_id;
  for (auto [x, y, r] : robots) {
    robots_id.push_back(id[x][y][r]);
  }
  vec<vec<int>> ways(k);
  for (int i = 0; i < k; i++) {
    vec<int> usd(cnt);
    int v = robots_id[i];
    while (true) {
      ways[i].push_back(v);
      if (usd[v])
        break;
      usd[v] = 1;
      v = go[i][v];
    }
  }
  vec<vec<int>> rays(k), cycs(k);
  vec<vec<int>> ray_fins(k), cyc_fins(k);
  for (int i = 0; i < k; i++) {
    int v = robots_id[i];
    while (v != ways[i].back()) {
      rays[i].push_back(v);
      if (fins.count(v)) {
        ray_fins[i].push_back(rays[i].size() - 1);
      }
      v = go[i][v];
    }
    cycs[i].push_back(v);
    if (fins.count(v)) {
      cyc_fins[i].push_back(cycs[i].size() - 1);
    }
    v = go[i][v];
    while (v != ways[i].back()) {
      cycs[i].push_back(v);
      if (fins.count(v)) {
        cyc_fins[i].push_back(cycs[i].size() - 1);
      }
      v = go[i][v];
    }
    if (cyc_fins.size() + ray_fins.size() == 0) {
      cout << "-1\n";
      return;
    }
  }
  int ans = INT64_MAX;
  for (int i = 0; i < k; i++) {
    for (int x : ray_fins[i]) {
      bool correct = true;
      for (int j = 0; j < k; j++) {
        if (x < rays[j].size()) {
          correct = fins.count(rays[j][x]);
          if (!correct)
            break;
        } else {
          correct = fins.count(cycs[j][(x - (int)rays[j].size()) % (int)cycs[j].size()]);
          if (!correct)
            break;
        }
      }
      if (correct) {
        ans = min(ans, x);
      }
    }
  }
  int mx = 1;
  for (int i = 0; i < k; i++) {
    mx *= cyc_fins[i].size();
  }
  for (int mask = 0; mask < mx; mask++) {
    vec<int> c_fins(k);
    int c_mask = mask;
    int max_ray = 0;
    for (int i = 0; i < k; i++) {
      c_fins[i] = c_mask % cyc_fins[i].size();
      c_mask /= cyc_fins[i].size();
      max_ray = max(max_ray, (int)rays[i].size());
    }
    vec<int> rems(k);
    for (int i = 0; i < k; i++) {
      rems[i] = ((cyc_fins[i][c_fins[i]] - (max_ray - (int)rays[i].size())) % (int)cycs[i].size() + cycs[i].size()) % cycs[i].size();
    }
    int a1 = rems[0];
    int n1 = cycs[0].size();
    bool failed = false;
    for (int i = 1; i < k; i++) {
      int a2 = rems[i];
      int n2 = cycs[i].size();
      auto X = solve_crt(a1, n1, a2, n2);
      if (!X.has_value()) {
        failed = true;
        break;
      }
      a1 = X.value();
      n1 = lcm(n1, n2);
    }
    if (!failed) {
      ans = min(ans, a1 + max_ray);
    }
  }
  if (ans == INT64_MAX) {
    cout << "-1\n";
    return;
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



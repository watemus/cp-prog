//
// Created by watemus on 06.09.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
/*
template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}*/

#ifdef LOCAL
#else
#endif

void run() {
  int n;
  cin >> n;
  vec<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  set<int> dif;
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    dif.insert(b[i]);
  }
  if (n <= 10) {
    vec<pair<int, int>> segs;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        segs.push_back({i, j});
      }
    }
    sort(ALL(segs), [&a](const pair<int, int> & aa, const pair<int, int> &bb){
        int mx1 = 0, mx2 = 0;
        for (int i = aa.first; i <= aa.second; i++) {
          mx1 = max(a[i], mx1);
        }
        for (int i = bb.first; i <= bb.second; i++) {
          mx2 = max(a[i], mx2);
        }
        return mx1 < mx2;
    });
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
      vec<int> ta = a;
      for (auto seg : segs) {
        int mx = 0;
        for (int i = seg.first; i <= seg.second; i++) {
          mx = max(a[i], mx);
        }
        bool ok = true;
        for (int i = seg.first; i <= seg.second; i++) {
          if ((mask & (1 << i)) && b[i] < mx) {
            ok = false;
            break;
          }
        }
        if (ok) {
          for (int i = seg.first; i <= seg.second; i++) {
            a[i] = mx;
          }
        }
      }
      int cans = 0;
      for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) cans++;
      }
      ans = max(ans, cans);
      a = ta;
    }
    cout << ans << '\n';
    return;
  } else if (n <= 5000 && dif.size() > 1) {
    vec<int> coords;
    for (int i = 0; i < n; i++) {
      coords.push_back(a[i]);
      coords.push_back(b[i]);
    }
    sort(ALL(coords));
    coords.resize(unique(ALL(coords)) - coords.begin());
    map<int, int> to;
    for (int i = 0; i < coords.size(); i++) {
      to[coords[i]] = i;
    }
    for (int i = 0; i < n; i++) {
      a[i] = to[a[i]];
      b[i] = to[b[i]];
    }
    vec<vec<int>> dp(n + 1, vec<int>(coords.size() + 1)), pdp(n + 1, vec<int>(coords.size() + 1));
    for (int i = n - 1; i >= 0; i--) {
      for (int j = coords.size() - 1; j >= 0; j--) {
        if (j >= a[i]) {
          dp[i][j] = pdp[i + 1][j];
          if (b[i] == j) {
            dp[i][j]++;
          }
        }
        pdp[i][j] = max(dp[i][j], pdp[i][j + 1]);
      }
    }
    cout << pdp[0][a[0]] << '\n';
    return;
  }
  vec<int> mask(n);
  for (int i = 0; i < n; i++) {
    if (a[i] == b[i]) {
      int j = i;
      while (j >= 0 && a[j] <= a[i] && !mask[j]) {
        mask[j] = 1;
        j--;
      }
      j = i + 1;
      while (j < n && a[j] <= a[i] && !mask[j]) {
        mask[j] = 1;
        j++;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (mask[i]) ans++;
  }
  cout << ans << "\n";
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



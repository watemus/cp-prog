//
// Created by watemus on 14.10.2020.
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

vec<int> combine(vec<int> &a, vec<int> &b) {
  vec<int> ans(a.size());
  for (int i = 0; i < ans.size(); i++) {
    ans[i] = b[a[i]];
  }
  return ans;
}

int get_val(vec<int> &p) {
  int ans = 0;
  for (int i = 0; i < p.size(); i++) {
    ans += (i + 1) * (p[i] + 1);
  }
  return ans;
}

void run() {
  int n, m;
  cin >> n >> m;
  vec<vec<int>> p(n, vec<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> p[i][j];
      p[i][j]--;
    }
  }
  if (n < m) {
    vec<vec<int>> ans(n, vec<int>(n));
    for (int i = 0; i < n; i++) {
      ans[i][i] = get_val(p[i]);
      auto cur = p[i];
      for (int j = i + 1; j < n; j++) {
        cur = combine(cur, p[j]);
        ans[i][j] = get_val(cur);
      }
    }
    int q;
    cin >> q;
    while (q--) {
      int l, r;
      cin >> l >> r;
      l--, r--;
      cout << ans[l][r] << '\n';
    }
  } else {
    vec<vec<int>> pref(n, vec<int>(m)), pref_rev(n, vec<int>(m));
    pref[n - 1] = p[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      pref[i] = combine(p[i], pref[i + 1]);
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        pref_rev[i][pref[i][j]] = j;
      }
    }
    int q;
    cin >> q;
    while (q--) {
      int l, r;
      cin >> l >> r;
      r--, l--;
      auto ans = pref[l];
      if (r < n - 1) {
        ans = combine(ans, pref_rev[r + 1]);
      }
      cout << get_val(ans) << '\n';
    }
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
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



//
// Created by watemus on 27.09.2020.
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

void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int cmask = 0;
  for (int i = 1; i <= 32; i++) {
    cmask += (1LL << i);
  }
  int ans = 0;
  int inv = 0;
  for (int i = 0; i < 32; i++) {
    unordered_map<int, vec<int>> mp;
    for (int j = 0; j < n; j++) {
      if (mp.count(cmask & a[j])) {
        mp[cmask & a[j]].push_back(bool(a[j] & (1LL << i)));
      } else {
        mp[cmask & a[j]] = {bool(a[j] & (1LL << i))};
      }
    }
    int cr, nw;
    cr = nw = 0;
    for (auto &[k, v] : mp) {
      int cnt[2] = {0, 0};
      for (int j : v) {
        if (j == 1) {
          nw += cnt[0];
        } else {
          cr += cnt[1];
        }
        cnt[j]++;
      }
    }
    if (nw < cr) {
      ans += (1LL << i);
    }
    inv += min(nw, cr);
    cmask -= (1LL << (i + 1));
  }
  cout << inv << ' ' << ans << '\n';
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



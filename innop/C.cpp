//
// Created by watemus on 22.11.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using namespace __gnu_pbds;

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

const int T = 2e9 + 10;
const int N = 1e7;

unordered_map<int, int> f;

void add(int at, int x) {
  for (int i = at; i < T; i += (i & -i)) {
    f[i] += x;
  }
}

int gt(int at) {
  int ans = 0;
  for (int i = at; i > 0; i -= (i & -i)) {
    ans += f[i];
  }
  return ans;
}

int get(int k) {
  int ans = 0;
  for (int i = 30; i >= 0; i--) {
    if (f[ans + (1LL << i)] < k) {
      ans += (1LL << i);
      k -= f[ans];
    }
  }
  return ans;
}

void run() {
  int n;
  cin >> n;
  f.reserve(N);
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    vec<pair<int, int>> a(m);
    for (auto &[w, c] : a) {
      cin >> w >> c;
    }
    sort(ALL(a));
    vec<pair<int, int>> na {a[0]};
    for (auto [w, c] : a) {
      if (c > na.back().second) {
        na.emplace_back(w, c);
      }
    }
    add(na[0].first, na[0].second);
    for (int j = 1; j < na.size(); j++) {
      add(na[j].first, na[j].second - na[j - 1].second);
    }
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    int cr = get(x);
    cr++;
    if (cr == 2147483648LL)
      cr = -1;
    cout << cr << ' ';
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



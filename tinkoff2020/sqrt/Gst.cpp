//
// Created by watemus on 11.10.2020.
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

void run() {
  int n, q;
  cin >> n >> q;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  while (q--) {
    int typ;
    cin >> typ;
    if (typ == 1) {
      int l, r;
      cin >> l >> r;
      l--, r--;
      map<int, int> cnt;
      for (int i = l; i <= r; i++) {
        cnt[a[i]]++;
      }
      set<int> st;
      for (auto [x, y] : cnt) {
        st.insert(y);
      }
      for (int i = 1; i <= n + 10; i++) {
        if (!st.count(i)) {
          cout << i << '\n';
          break;
        }
      }
    } else {
      int p, x;
      cin >> p >> x;
      p--;
      a[p] = x;
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



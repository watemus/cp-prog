//
// Created by watemus on 13.10.2020.
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

#define int __int128

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

#ifdef LOCAL
#else
#endif

int pw(int a, int b, int mod) {
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
      ans %= mod;
    }
    a *= a;
    a %= mod;
    b >>= 1;
  }
  return ans;
}

void run() {
  ll n, a;
  cin >> n >> a;
  vec<pair<int, int>> st;
  vec<pair<int, int>> ste;
  st.emplace_back(INFL, 0);
  int ans = 0;
  int phi = (1LL << 31);
  int mod = (1LL << 32);
  for (int i = 1; i <= n; i++) {
    while (st.back().first <= a) {
      st.pop_back();
    }
    ans -= st.back().second + 1;
    st.emplace_back(a, i);
    a = (a * 214013 + 2531011) % (1LL << 32);
  }
  st = {{INFL, n + 1}};
  int rev = pw(214013, phi - 1, mod);
  for (int i = n; i >= 1; i--) {
    a = ((a - 2531011) + mod) % mod * rev % mod;
    while (st.back().first <= a) {
      st.pop_back();
    }
    ans += st.back().second;
    st.emplace_back(a, i);
  }
  cout << (ll)ans << '\n';
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



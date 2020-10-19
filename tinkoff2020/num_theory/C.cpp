//
// Created by watemus on 01.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#else

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")

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

const int MAXN = 2e6 + 10;
const int MOD = 1e9 + 7;

inline int pw(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
      ans %= MOD;
    }
    a *= a;
    a %= MOD;
    b >>= 1;
  }
  return ans;
}

void run() {
  int n, k;
  cin >> n >> k;
  vec<int> cnt_diff(MAXN), cnt_all(MAXN), lp(MAXN), fact(MAXN), inv_fact(MAXN), inv(MAXN);
  fact[0] = 1;
  fact[1] = 1;
  inv_fact[0] = inv_fact[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    fact[i] = fact[i - 1] * i % MOD;
    inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
    inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
  }
  int cnt_prm = 0;
  vec<int> primes;
  for (int i = 2; i <= n; i++) {
    if (lp[i] == 0) {
      lp[i] = i;
      primes.push_back(i);
      cnt_prm++;
    }
    for (int j = 0; j < primes.size() && primes[j] <= lp[i] && primes[j] * i <= n; j++) {
      lp[primes[j] * i] = primes[j];
    }
  }
  for (int i = 2; i <= n; i++) {
    cnt_all[i] = cnt_all[i / lp[i]] + 1;
    cnt_diff[i] = cnt_diff[i / lp[i]];
    if (i / lp[i] % lp[i]) {
      cnt_diff[i]++;
    }
  }
  // cout << 0 << '\n';
  int ans = 0;
#define C(n, k) fact[n + k - 1] % MOD * inv_fact[k] % MOD * inv_fact[n - 1] % MOD

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      int diff_all = cnt_all[j] - cnt_all[i];
      int diff_prm = cnt_diff[gcd(j, j / i)];
      if (diff_all <= k) {
        ans += j * C(cnt_prm - diff_prm + 1, k - diff_all);
      }
    }
  }
  cout << ans % MOD << '\n';
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



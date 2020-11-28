//
// Created by watemus on 15.11.2020.
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

const int MOD = 998244353;

void ntt(vec<int> &s, vec<int> &ans, int n, int t, int a, int b, int c) {
  if (n == 1) {
    ans[c] = s[a];
  } else {
    ntt(s, ans, n / 2, t * t % MOD, a, b * 2, c);
    ntt(s, ans, n / 2, t * t % MOD, a + b, b * 2, c + n / 2);
    int x = 1;
    for (int i = 0; i < n / 2; i++) {
      int an1 = ans[c + i];
      int an2 = ans[c + i + n / 2];
      ans[c + i] = (an1 + x * an2) % MOD;
      ans[c + i + n / 2] = ((an1 - x * an2) % MOD + MOD) % MOD;
      x = (x * t) % MOD;
    }
  }
}

int pw(int a, int b) {
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
  int k;
  cin >> k;
  int n = 1 << (k + 1);
  int t = pw(31, 1 << (23 - k - 1));
  vec<int> a(n * 2), b(n * 2);
  for (int i = 0; i < n / 2; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n / 2; i++) {
    cin >> b[i];
  }
  vec<int> ans_a(n), ans_b(n);
  ntt(a, ans_a, n, t, 0, 1, 0);
  ntt(b, ans_b, n, t, 0, 1, 0);
  for (int i = 0; i < n; i++) {
    ans_a[i] = (ans_a[i] * ans_b[i]) % MOD;
  }
  vec<int> ans(n);
  int rev = pw(n, MOD - 2);
  ntt(ans_a, ans, n, pw(t, MOD - 2), 0, 1, 0);
  for (int i = 0; i < n; i++) {
    cout << ans[i] * rev % MOD << ' ';
  }
  cout << '\n';
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



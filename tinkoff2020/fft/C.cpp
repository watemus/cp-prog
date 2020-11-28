//
// Created by watemus on 16.11.2020.
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

const int N = (1 << 21);

int arr1[N + 10];
int arr2[N + 10];
int mask1[N + 10];
int mask2[N + 10];

const int MOD = 998244353;
const int W = 482;

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

void ntt(int *s, int *ans, int n, int t, int a, int b, int c) {
  if (n == 1) {
    ans[c] = s[a];
  } else {
    ntt(s, ans, n / 2, t * t % MOD, a, b * 2, c);
    ntt(s, ans, n / 2, t * t % MOD, a + b, b * 2, c + n / 2);
    int x = 1;
    for (int i = c; i < c + n / 2; i++) {
      int an1 = ans[i];
      int an2 = ans[i + n / 2];
      ans[i] = (an1 + x * an2) % MOD;
      ans[i + n / 2] = ((an1 - x * an2) % MOD + MOD) % MOD;
      x *= t;
      x %= MOD;
    }
  }
}

int t1[N + 10];
int t2[N + 10];
int ans1[N + 10];
int ans2[N + 10];

void convolution(int *a, int *b, int *c) {
  ntt(a, t1, N, W, 0, 1, 0);
  ntt(b, t2, N, W, 0, 1, 0);
  for (int i = 0; i < N; i++) {
    t1[i] *= t2[i];
    t1[i] %= MOD;
  }
  ntt(t1, c, N, pw(W, MOD - 2), 0, 1, 0);
  int rev = pw(N, MOD - 2);
  for (int i = 0; i < N; i++) {
    c[i] = (c[i] * rev) % MOD;
  }
}

void run() {
  string s, t;
  cin >> s >> t;
  for (int i = 0; i < s.size(); i++) {
    int cr = 0;
    if ('0' <= s[i] && s[i] <= '9') {
      cr = s[i] - '0';
    } else {
      cr = s[i] - 'A' + 10;
    }
    for (int j = 0; j < 4; j++) {
      arr1[i * 4 + 3 - j] = bool(cr & (1 << j));
      arr2[i * 4 + 3 - j] = 1 - bool(cr & (1 << j));
    }
  }
  for (int i = 0; i < t.size(); i++) {
    int cr0, cr1;
    if (t[i] == '?') {
      cr0 = 1;
      cr1 = 1;
    } else {
      cr0 = (t[i] == '1');
      cr1 = 1 - cr0;
    }
    mask1[t.size() - i - 1] = cr0;
    mask2[t.size() - i - 1] = cr1;
  }
  convolution(arr1, mask1, ans1);
  convolution(arr2, mask2, ans2);
  for (int i = 0; i + t.size() <= s.size() * 4; i += 8) {
    cout << ans1[i + t.size() - 1] + ans2[i + t.size() - 1] << ' ';
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



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

struct BigInt {
  int len;
  int *digits;
  BigInt() {
    len = 1;
    digits = new int[1];
    digits[0] = 0;
  }
  BigInt(int *new_digits, int n) {
    len = n;
    digits = new int[n + 10];
    memcpy(digits, new_digits, sizeof(int) * n);
  }
  BigInt(const BigInt &oth) {
    len = oth.len;
    digits = new int[len + 10];
    memcpy(digits, oth.digits, sizeof(int) * len);
  }
  BigInt &operator=(const BigInt &oth) {
    len = oth.len;
    digits = new int[len + 10];
    memcpy(digits, oth.digits, sizeof(int) * len);
    return *this;
  }
  ~BigInt() {
    delete[] digits;
  }
};

const int N = 1 << 19;

namespace ntt {
  int c1[N];
  int c2[N];
  int res[N];
  const int MOD = 998244353;
  const int W = 7677;
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
  int gst(int a) {
    int ans = 0;
    while (a != 1) {
      a *= a;
      a %= MOD;
      ans++;
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
  void convolution(int *a, int *b, int *c, int n) {
    ntt(a, c1, n, W, 0, 1, 0);
    ntt(b, c2, n, W, 0, 1, 0);
    for (int i = 0; i < n; i++) {
      c1[i] *= c2[i];
      c1[i] %= MOD;
    }
    ntt(c1, c, n, pw(W, MOD - 2), 0, 1, 0);
    int rev = pw(n, MOD - 2);
    for (int i = 0; i < n; i++) {
      c[i] *= rev;
      c[i] %= MOD;
    }
  }
}

BigInt operator+(BigInt &a, BigInt &b) {
  int res_len = max(a.len, b.len);
  int last = 1;
  if (a.len == res_len) {
    last += a.digits[a.len - 1];
  }
  if (b.len == res_len) {
    last += b.digits[b.len - 1];
  }
  if (last >= 10) {
    res_len *= 2;
  }
  int *res = new int[res_len];
  int carry = 0;
  for (int i = 0; i < res_len; i++) {
    res[i] = a.digits[i] + b.digits[i] + carry;
    carry = res[i] / 10;
    res[i] %= 10;
  }
  return BigInt(res, res_len);
}

BigInt operator-(BigInt &a, BigInt &b) {
  int res_len = max(a.len, b.len);
  int *res = new int[res_len];
  int carry = 0;
  for (int i = 0; i < res_len; i++) {
    res[i] = a.digits[i] - b.digits[i] - carry;
    if (res[i] < 0) {
      res[i] += 10;
      carry = 1;
    } else {
      carry = 0;
    }
  }
  return BigInt(res, res_len);
}

BigInt operator*(BigInt &a, BigInt &b) {
  int res_len = max(a.len * 2, b.len * 2);
  int *res = new int[res_len];
  ntt::convolution(a.digits, b.digits, res, res_len);
  int carry = 0;
  for (int i = 0; i < res_len; i++) {
    res[i] += carry;
    carry = res[i] / 10;
    res[i] %= 10;
  }
  return BigInt(res, res_len);
}

BigInt unite(vec<reference_wrapper<BigInt>> v) {
  int sm = 0;
  for (auto &d : v) {
    sm += d.len;
  }
  int res_len = 1;
  while (res_len < sm) {
    res_len *= 2;
  }
  int *res = new int[res_len];
  int ptr = 0;
  for (auto &d : v) {
    for (int i = 0; i < d.len; i++) {
      res[ptr++] = d.digits[i];
    }
  }
  return BigInt(res, res_len);
}

pair<BigInt, BigInt> divide2(BigInt &a) {
  BigInt t1(a.digits, a.len / 2), t2(a.digits + a.len / 2, a.len / 2);
  return {t1, t2};
}

tuple<BigInt, BigInt, BigInt, BigInt> divide4(BigInt &a) {
  BigInt t1(a.digits, a.len / 4);
  BigInt t2(a.digits + a.len / 4, a.len / 4);
  BigInt t3(a.digits + a.len / 2, a.len / 4);
  BigInt t4(a.digits + a.len / 4 * 3, a.len / 4);
  return {t1, t2, t3, t4};
}

pair<BigInt, BigInt> recursive_div(BigInt &a, BigInt &b);
pair<BigInt, BigInt> div32(BigInt &a1, BigInt &a2, BigInt &a3, BigInt &b1, BigInt &b2);

pair<BigInt, BigInt> div32(BigInt &a1, BigInt &a2, BigInt &a3, BigInt &b1, BigInt &b2) {
  auto a12 = unite({a1, a2});
  auto [q, c] = recursive_div(a12, b1);
  auto d = q * b2;

}

pair<BigInt, BigInt> recursive_div(BigInt &a, BigInt &b) {

}

BigInt operator/(BigInt &a, BigInt &b) {

}

void run() {

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



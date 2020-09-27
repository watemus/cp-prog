//
// Created by watemus on 22.08.2020.
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
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int mod = 1e9 + 7;

int fpw(int a, int b) {
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
  string a, b;
  cin >> a >> b;
  a = string(b.size() - a.size(), '0') + a;
  int n = a.size();
  int tn = n - 1;
  while (a[tn] == '0') {
    a[tn] = '9';
    tn--;
  }
  a[tn] = a[tn] - 1;
  vec<int> ca(n), cb(n);
  ca[0] = a[0] - '0', cb[0] = b[0] - '0';
  for (int i = 1; i < n; i++) {
    ca[i] = ((ca[i - 1] * 10) + a[i] - '0') % mod;
    cb[i] = ((cb[i - 1] * 10) + b[i] - '0') % mod;
  }
  reverse(ALL(ca));
  reverse(ALL(cb));
  reverse(ALL(a));
  reverse(ALL(b));
  ca.push_back(0), cb.push_back(0);
  a.push_back('0'), b.push_back('0');
  auto make_cnt = [](vec<int> &ca, string &a) {
    int n = a.size() - 1;
    vec<array<int, 10>> cnt(n);
    int pw = 1;
    int psum = 0;
    for (int i = 0; i < n; i++) {
      int dt = pw * (a[i] - '0') % mod;
      int cnt_mn = (ca[i] * pw % mod - dt + mod) % mod;
      for (int j = 0; j < 10; j++) {
        cnt[i][j] = cnt_mn * fpw(10, mod - 2) % mod;
      }
      for (int j = 0; j < a[i] - '0'; j++) {
        cnt[i][j] += pw;
        cnt[i][j] %= mod;
      }
      int j = a[i] - '0';
      cnt[i][j] += psum + 1;
      cnt[i][j] %= mod;
      psum = (psum + pw * (a[i] - '0') % mod) % mod;
      pw *= 10;
      pw %= mod;
    }
    return cnt;
  };
  auto cnt_a = make_cnt(ca, a);
  auto cnt_b = make_cnt(cb, b);
  vec<array<int, 10>> cnt(n);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 10; j++) {
      cnt[i][j] = (cnt_b[i][j] - cnt_a[i][j] + mod) % mod;
    }
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 10; k++) {
        ans += abs(k - j) * cnt[i][j] % mod * cnt[i][k] % mod;
        ans %= mod;
      }
    }
  }
  cout << ans << '\n';
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



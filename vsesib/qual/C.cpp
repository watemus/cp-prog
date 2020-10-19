//
// Created by watemus on 18.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

struct HashSystem {
  int p, mod;
  inline int add(int a, int b) {
    a += b;
    if (a >= mod)
      a -= mod;
    return a;
  }
  inline int sub(int a, int b) {
    a -= b;
    if (a < 0)
      a += mod;
    return a;
  }
  inline int mul(int a, int b) {
    return a * b % mod;
  }
  vec<int> ps, hs;
  HashSystem(string &s, int p, int mod) : ps(s.size()), hs(s.size()), p(p), mod(mod) {
    ps[0] = 1;
    hs[0] = s[0] - '0' + 1;
    for (int i = 1; i < s.size(); i++) {
      ps[i] = mul(ps[i - 1], p);
      hs[i] = add(mul(hs[i - 1], p), s[i] - '0' + 1);
    }
  }
  inline int get(int l, int r) {
    int ans = hs[r];
    if (l > 0) {
      ans = sub(ans, mul(hs[l - 1], ps[r - l + 1]));
    }
    return ans;
  }
};

const int p1 = 11, p2 = 13, m1 = 1e9 + 7, m2 = 1e9 + 9;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
  int operator()(int x) const { return x ^ RANDOM; }
};


void run() {
  string s;
  cin >> s;
  HashSystem h1(s, 11, 1e9 + 7);
  HashSystem h2(s, 13, 1e9 + 9);
  int n = s.size();
  int q;
  cin >> q;
  int ans = 0;
  unordered_map<int, int> cnt;
  cnt.reserve(q + 19);
  while (q--) {
    string t;
    cin >> t;
    int b;
    cin >> b;
    int t1 = 0;
    int t2 = 0;
    for (int i = 0; i < t.size(); i++) {
      t1 = h1.add(t[i] - '0' + 1, h1.mul(t1, p1));
      t2 = h2.add(t[i] - '0' + 1, h2.mul(t2, p2));
    }
    cnt[t1 * t2] += b;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < min(i + 21, n); j++) {
      int h = h1.get(i, j) * h2.get(i, j);
      if (cnt.count(h)) {
        ans += cnt[h];
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



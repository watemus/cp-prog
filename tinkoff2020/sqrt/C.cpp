//
// Created by watemus on 10.10.2020.
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

int K = 10;

struct HashSystem {
  int p, mod;
  vec<int> hs, ps;
  inline int add(int a, int b) const {
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
    return a * 1ll * b % mod;
  }
  HashSystem(string &s, int p, int mod)
  : hs(s.size()), ps(s.size()), p(p), mod(mod) {
    ps[0] = 1;
    hs[0] = s[0] - 'a' + 1;
    for (int i = 1; i < s.size(); i++) {
      hs[i] = add(mul(hs[i - 1], p), s[i] - 'a' + 1);
      ps[i] = mul(ps[i - 1], p);
    }
  }
  int get(int l, int r) {
    int ans = hs[r];
    if (l > 0) {
      ans = sub(ans, mul(hs[l - 1], ps[r - l + 1]));
    }
    return ans;
  }
};

void run() {
  string s;
  cin >> s;
  int m;
  cin >> m;
  unordered_map<int, vec<signed>> mp;
  mp.reserve(s.size() * K);
  int n = s.size();
  HashSystem h1(s, 31, 1e9 + 7);
  HashSystem h2(s, 31, 1e9 + 9);
  for (int i = 0; i < n; i++) {
    for (int j = i; j < min(n, i + K); j++) {
      int mm = h1.get(i, j) * h2.get(i, j);
      if (mp.count(mm)) {
        mp[mm].push_back(i);
      } else {
        mp[mm] = {(signed)i};
      }
    }
  }
  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;
    string t;
    cin >> t;
    int t1 = 0, t2 = 0;
    for (int j = 0; j < t.size(); j++) {
      t1 = h1.add(h1.mul(t1, h1.p), t[j] - 'a' + 1);
      t2 = h2.add(h2.mul(t2, h2.p), t[j] - 'a' + 1);
    }
    if (t.size() < K && mp.count(t1 * t2) && mp[t1 * t2].size() >= k) {
      auto &vc = mp[t1 * t2];
      int i1 = 0;
      int i2 = k - 1;
      int ans = INFI;
      while (i2 < vc.size()) {
        ans = min(ans, vc[i2] + (int)t.size() - vc[i1]);
        i2++;
        i1++;
      }
      cout << ans << "\n";
    } else if (t.size() >= K) {
      vec<signed> vc;
      for (int j = 0; j + t.size() - 1 < n; j++) {
        if (h1.get(j, j + t.size() - 1) == t1 && h2.get(j, j + t.size() - 1) == t2) {
          vc.push_back(j);
        }
      }
      int i1 = 0;
      int i2 = k - 1;
      if (i2 >= vc.size()) {
        cout << "-1\n";
        continue;
      }
      int ans = INFI;
      while (i2 < vc.size()) {
        ans = min(ans, vc[i2] + (int)t.size() - vc[i1]);
        i2++;
        i1++;
      }
      cout << ans << "\n";
    } else {
      cout << "-1\n";
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



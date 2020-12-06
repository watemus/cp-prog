//
// Created by watemus on 04.12.2020.
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

const int N = 3e6 + 10;

int sm[N];

void add_leafs(int v) {
  if (sm[v * 2] == 0) {
    sm[v * 2] = v * 2;
  } else {
    add_leafs(v * 2);
  }
  if (sm[v * 2 + 1] == 0) {
    sm[v * 2 + 1] = v * 2 + 1;
  } else {
    add_leafs(v * 2 + 1);
  }
  sm[v] = sm[v * 2 + 1] + sm[v * 2] + v;
}

const int MOD = 1e9 + 7;

int pw(int a, int b) {
  int ans = 1;
  while (b > 0) {
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

int k[N], b[N];

void run() {
  int m;
  cin >> m;
  sm[1] = 1;
  if (m <= 20) {
    for (int i = 0; i < m; i++) {
      string op;
      cin >> op;
      int v;
      cin >> v;
      if (op == "Grow") {
        add_leafs(v);
        while (v > 0) {
          sm[v] = sm[v * 2] + sm[v * 2 + 1] + v;
          v /= 2;
        }
      } else {
        cout << sm[v] << '\n';
      }
    }
  } else {
    vec<pair<int, int>> queries(m);
    int cc1 = 0, cc2 = 0;
    int c1 = 0, c2 = 0;
    for (auto &[tp, v] : queries) {
      string op;
      cin >> op >> v;
      if (op == "Grow") {
        tp = 1;
        c1++;
        if (v == 1) {
          cc1++;
        }
      } else {
        tp = 2;
        c2++;
        if (v == 1) {
          cc2++;
        }
      }
    }
    if (c1 == cc1) {
      int h = 1;
      k[1] = 1;
      b[1] = 0;
      for (int i = 2; i < N; i++) {
        k[i] = k[i - 1] + pw(4, i - 1);
        k[i] %= MOD;
        b[i] = b[i - 1] + pw(2, i - 1) * (pw(2, i - 1) - 1) / 2;
        b[i] %= MOD;
      }
      for (auto [tp, v] : queries) {
        if (tp == 1) h++;
        else {
          int cv = v;
          int ch = 0;
          while (cv > 0) {
            ch++;
            cv /= 2;
          }
          cout << (v * k[h - ch + 1] + b[h - ch + 1]) % MOD << '\n';
        }
      }
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



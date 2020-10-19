//
// Created by watemus on 18.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif



#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>


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

const int mod = 1e9 + 9;
const int M = 6;
const int N = 1001;
const int M6 = 729;

signed dp1[N][M6];

int n, m, k;
int m6 = 1;
inline void get_digs(int mask, int *digs) {
  for (int j = 0; j < m; j++) {
    digs[j] = (mask % 3);
    mask /= 3;
  }
}

signed good[N][M6];
signed t[N][M];
signed **trans;

void calc() {
  for (int i = 1; i < n; i++) {
    for (int pmask = 0; pmask < m6; pmask++) {
      if (!good[i - 1][pmask])
        continue;
      for (int mask = 0; mask < m6; mask++) {
        if (!good[i][mask])
          continue;
        dp1[i][mask] += dp1[i - 1][pmask] * trans[pmask][mask];
        if (dp1[i][mask] >= mod) {
          dp1[i][mask] -= mod;
        }
      }
    }
  }
}

void mul(signed **a, signed **b, signed **c) {
  for (int i = 0; i < m6; i++) {
    for (int j = 0; j < m6; j++) {
      for (int h = 0; h < m6; h++) {
        c[i][j] += a[i][h] * 1ll * b[h][j] % mod;
        c[i][j] %= mod;
      }
    }
  }
}

void cpy(signed **a, signed **b) {
  for (int i = 0; i < m6; i++) {
    memcpy(a[i], b[i], sizeof(signed) * m6);
  }
}

signed **aa, **bb, **tmp;
signed **one;

void print(signed **a) {
  for (int i = 0; i < m6; i++) {
    for (int j = 0; j < m6; j++) {
      cout << a[i][j] << ' ';
    }
    cout << '\n';
  }
}

void pw(signed **a, signed **res, int b) {
  cpy(res, trans);
  //print(trans);
  print(res);
  while (b) {
    if (b & 1) {
      mul(res, a, tmp);
      cpy(res, tmp);
      print(res);
    }
    mul(a, a, tmp);
    cpy(a, tmp);
    b >>= 1;
  }
}


void run() {
  cin >> n >> m >> k;
  swap(n, m);
  for (int i = 0; i < m; i++) {
    m6 *= 3;
  }
  int digs[6];
  int pdigs[6];
  trans = new signed*[M6];
  aa = new signed*[M6];
  bb = new signed*[M6];
  tmp = new signed*[M6];
  one = new signed*[M6];
  for (int pmask = 0; pmask < m6; pmask++) {
    trans[pmask] = new signed[M6];
    aa[pmask] = new signed[M6];
    bb[pmask] = new signed[M6];
    tmp[pmask] = new signed[M6];
    one[pmask] = new signed[M6];
    for (int mask = 0; mask < m6; mask++) {
      get_digs(pmask, pdigs);
      get_digs(mask, digs);
      bool correct = true;
      vec<int> twos;
      for (int j = 0; j < m; j++) {

        if (digs[j] == 2 && pdigs[j] != 0) {
          correct = false;
          break;
        } else if (digs[j] == 2) {
          twos.push_back(j);
        }
      }
      for (int j = 1; j < twos.size(); j += 2) {
        if (twos[j] - 1 != twos[j - 1]) {
          correct = false;
          break;
        }
      }
      if (twos.size() % 2) {
        correct = false;
      }
      if (correct)
        one[pmask][mask] = 1;
      else
        one[pmask][mask] = 0;
      trans[pmask][mask] = correct;
    }
  }
  if (false) {
    for (int i = 0; i < m6; i++) {
      get_digs(i, digs);
      bool was = false;
      for (int j = 0; j < m; j++) {
        if (digs[j] == 2) {
          was = true;
          break;
        }
      }
      dp1[0][i] = !was;
    }
    for (int i = 0; i < k; i++) {
      int x, y;
      cin >> y >> x;
      x--, y--;
      t[x][y] = 1;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m6; j++) {
        bool ok = true;
        get_digs(j, digs);
        for (int h = 0; h < m; h++) {
          if (t[i][h] == 1 && digs[h] != 1) {
            ok = false;
            break;
          }
        }
        if (ok)
          good[i][j] = 1;
      }
    }
    calc();
    int ans = 0;
    for (int i = 0; i < m6; i++) {
      ans += dp1[n - 1][i];
      ans %= mod;
    }
    cout << ans << '\n';
  } else {
    cpy(bb, trans);
    pw(bb, aa, n - 3);
    int ans = 0;
    for (int i = 0; i < m6; i++) {
      for (int j = 0; j < m6; j++) {
        ans += aa[i][j];
        ans %= mod;
      }
    }
    cout << ans << '\n';
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



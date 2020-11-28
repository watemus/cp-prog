//
// Created by watemus on 05.11.2020.
//
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
//
// Created by watemus on 05.11.2020.
//

#include "immintrin.h"
#include <bits/stdc++.h>

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")


unsigned GetMin(unsigned *a, int n) {
  __m256i mn = _mm256_set1_epi32(UINT32_MAX);
  size_t i = 0;
  for (; i + 8 <= n; i += 8) {
    mn = _mm256_min_epu32(*reinterpret_cast<const __m256i*>(a + i), mn);
  }
  unsigned ans = UINT32_MAX;
  for (; i < n; i++) {
    ans = std::min(ans, a[i]);
  }
  auto *block = reinterpret_cast<unsigned*>(&mn);
  for (i = 0; i < 8; i++) {
    ans = std::min(ans, block[i]);
  }
  return ans;
}

void AddProg(unsigned *a, int n, unsigned k) {
  unsigned k8 = k * 8;
  __m256i dt = _mm256_setzero_si256();
  __m256i st = _mm256_set1_epi32(k8);
  auto *block = reinterpret_cast<unsigned*>(&dt);
  block[0] = k;
  for (int i = 1; i < 8; i++) {
    block[i] = block[i - 1] + k;
  }
  size_t i = 0;
  for (; i + 8 <= n; i += 8) {
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(a + i), _mm256_add_epi32(*reinterpret_cast<const __m256i*>(a + i), dt));
    dt = _mm256_add_epi32(dt, st);
  }
  unsigned lst = block[7] - k8;
  for (; i < n; i++) {
    a[i] += lst + k;
    lst += k;
  }
}

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

const int N = 20;

unsigned a[N];

void run() {
  AddProg(a, N, 1);
  for (int i = 0; i < N; i++) {
    cout << a[i] << ' ';
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




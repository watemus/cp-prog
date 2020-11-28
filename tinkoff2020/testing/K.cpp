//
// Created by watemus on 05.11.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <immintrin.h>
#include <bits/stdc++.h>


#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

// #define int ll

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

const int N = 2e5 + 10;
unsigned a[N];

void run() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  while (k--) {
    int l1, l2, len;
    cin >> l1 >> l2 >> len;
    l1--, l2--;
    size_t i = 0;
    for (i = 0; i + 8 <= len; i += 8) {
      __m256i cr = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(a + l2 + i));
      __m256i dt = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(a + l1 + i));
      cr = _mm256_add_epi32(cr, dt);
      _mm256_storeu_si256(reinterpret_cast<__m256i *>(a + l2 + i), cr);
    }
    for (; i < len; i++) {
      a[l2 + i] += a[l1 + i];
    }
  }
  for (int i = 0; i < n; i++) {
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



//
// Created by watemus on 16.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#else
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("vpt")
#endif

#include <bits/stdc++.h>


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

const int N = 2e5;
const int K = 1 << 11;

int a[N];
int b[K][K];
int bb[K][K + 1];
int bi[K][K + 1];
int bs[K];
int trash[K];


int eytzinger(int i, int k, int *ar, int *br, int *bbi, int sz) {
  if (k <= sz) {
    i = eytzinger(i, 2 * k, ar, br, bbi, sz);
    br[k] = ar[i++];
    i = eytzinger(i, 2 * k + 1, ar, br, bbi, sz);
  }
  return i;
}

int eytzingeri(int i, int k, int *ar, int *br, int *bbi, int sz) {
  if (k <= sz) {
    i = eytzingeri(i, 2 * k, ar, br, bbi, sz);
    bbi[k] = i++;
    i = eytzingeri(i, 2 * k + 1, ar, br, bbi, sz);
  }
  return i;
}


int search(int x, int *br, int *bbi, int sz) {
  int k = 1;
  while (k <= sz) {
    __builtin_prefetch(br + k * 16);
    k = 2 * k + (br[k] < x);
  }
  k >>= __builtin_ffs(~k);
  return bbi[k];
}


void run() {
  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    b[i / K][i % K] = a[i];
    bs[i / K]++;
    if (i == n - 1 || i % K == K - 1) {
      sort(b[i / K], b[i / K] + bs[i / K]);
      bi[i / K][0] = bs[i / K];
      eytzinger(0, 1, b[i / K], bb[i / K], bi[i / K], bs[i / K]);
      eytzingeri(0, 1, b[i / K], bb[i / K], bi[i / K], bs[i / K]);
    }
  }
  cin >> q;
  while (q--) {
    int typ;
    cin >> typ;
    if (typ == 1) {
      int i, x;
      cin >> i >> x;
      i--;
      int ik = i / K;
      int im = i % K;
      int jj = 0;
      for (int j = 0; j < bs[ik]; j++) {
        if (b[ik][j] == a[i]) {
          jj = j;
          break;
        }
      }
      for (int j = jj; j + 1 < bs[ik]; j++) {
        b[ik][j] = b[ik][j + 1];
      }
      int arr[1];
      arr[0] = x;
      merge(arr, arr + 1, b[ik], b[ik] + bs[ik] - 1, trash);
      a[i] = x;
      memcpy(b[ik], trash, bs[ik] * sizeof(int));
      bi[i / K][0] = bs[i / K];
      eytzinger(0, 1, b[i / K], bb[i / K], bi[i / K], bs[i / K]);
    } else {
      int l, r, m;
      cin >> m >> l >> r;
      int tl = l;
      l--;
      int cnt = 0;
      int to = min((l) / K * K + K, r);
      for (; l < to; l++) {
        if (a[l] < m) cnt--;
      }
      while (l + K <= r) {
        ll kk = search(m, bb[l / K], bi[l / K], bs[l / K]);
        cnt -= kk;
        l += K;
      }
      for (; l < r; l++) {
        if (a[l] < m) cnt--;
      }
      cout << max((r - tl + 1) + 2 * cnt, (int)0) << '\n';
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



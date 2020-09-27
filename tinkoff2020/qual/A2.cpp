//
// Created by watemus on 23.08.2020.
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

void run() {
  int n, m, k;
  cin >> n >> m >> k;
  int block_shift = 0;
  vec<int> st(m), nd(m);
  for (int i = 0; i < k; i++) {
    int tp, shift;
    cin >> tp >> shift;
    //shift = -shift;
    if (tp == 2) {
      //shift = -shift;
      shift = (shift % n + n) % n;
      st.front() += shift / m;
      nd.back() += shift / m;
      shift %= m;
      if (shift > 0) {
        int _end = (m - block_shift - 1) % m;
        nd[_end]++;
        int _beg = _end - shift + 1;
        if (_beg < 0) {
          st[m + _beg]++;
          nd[m - 1]++;
          st[0]++;
        } else {
          st[_beg]++;
        }
      }
      block_shift += shift;
      block_shift %= m;
    } else {
      shift = (shift % m + m) % m;
      block_shift += shift;
      block_shift %= m;
    }
  }
  int cur = 0;
  vec<int> p(n);
  for (int i = 0; i < m; i++) {
    cur += st[i];
    for (int j = 0; j < n / m; j++) {
      p[((block_shift + i) % m + cur * m + j * m) % n] = j * m + i;
    }
    cur -= nd[i];
  }
  vec<int> ans(n);
  for (int i = 0; i < n; i++) {
    int el;
    cin >> el;
    ans[p[i]] = el;
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



//
// Created by watemus on 06.09.2020.
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

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
/*
template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}*/

#ifdef LOCAL
#else
#endif

void run() {
  int n;
  cin >> n;
  int q;
  cin >> q;
  vec<int> diam(n), cap(n);
  for (int i = 0; i < n; i++) {
    cin >> diam[i] >> cap[i];
  }
  diam.push_back(INFI);
  cap.push_back(INFI);
  vec<pair<int, int>> st;
  st.push_back({n, INFI});
  vec<int> to(n + 1, n);
  for (int i = n - 1; i >= 0; i--) {
    while (diam[i] >= st.back().second) {
      st.pop_back();
    }
    to[i] = st.back().first;
    st.push_back({i, diam[i]});
  }
  const int LOGN = 18;
  vec<vec<int>> up(LOGN, vec<int>(n + 1));
  vec<vec<int>> have(LOGN, vec<int>(n + 1));
  for (int i = n; i >= 0; i--) {
    up[0][i] = to[i];
    have[0][i] = cap[i];
    for (int j = 1; j < LOGN; j++) {
      up[j][i] = up[j - 1][up[j - 1][i]];
      have[j][i] = have[j - 1][i] + have[j - 1][up[j - 1][i]];
      //cout << have[j][i] << ':';
    }
    //cout << endl;
  }
  for (int i = 0; i < q; i++) {
    int at, rem;
    cin >> at >> rem;
    at--;
    for (int j = LOGN - 1; j >= 0; j--) {
      if (have[j][at] < rem) {
        rem -= have[j][at];
        at = up[j][at];
      }
    }
    if (at == n) {
      cout << "0\n";
    } else {
      cout << at + 1 << '\n';
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}



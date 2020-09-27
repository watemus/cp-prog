//
// Created by watemus on 08.09.2020.
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

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

int ask(int i, int j) {
  cout << "? " << i + 1 << ' ' << j + 1 << endl;
  int ans;
  cin >> ans;
  return ans;
}

void run() {
  int n;
  cin >> n;
  vec<int> p(n);
  int mx = 0;
  for (int i = 1; i < n; i++) {
    int t1 = ask(mx, i);
    int t2 = ask(i, mx);
    if (t1 > t2) {
      mx = i;
    } else {
      p[i] = t2;
    }
  }
  set<int> st;
  for (int i = 1; i <= n; i++) {
    st.insert(i);
  }
  for (int i = 0; i < n; i++) {
    if (st.count(p[i])) st.erase(p[i]);
  }
  for (int i = 0; i < n; i++) {
    if (p[i] == 0) {
      p[i] = *st.begin();
      st.erase(st.begin());
    }
  }
  cout << "! ";
  for (int i = 0; i < n; i++) {
    cout << p[i] << ' ';
  }
  cout << endl;
}

signed main() {
#ifdef LOCAL
  //std::freopen("input.txt", "r", stdin);
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



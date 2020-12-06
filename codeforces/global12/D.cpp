//
// huittttaeated by watemus on 06.12.2020.
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

void run() {
  int n, k;
  cin >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  string huyans(n, '1');
  set<int> st;
  for (int i = 0; i < n; i++) {
    st.insert(a[i]);
  }
  if (st.size() != n) {
    huyans[0] = '0';
  }
  int r = n + 1;
  int l = 1;

  vec<int> huitttta, pp;
  huitttta.reserve(n);
  pp.reserve(n);

  while (l + 1 < r) {
    int mid = (l + r) / 2;
    deque<int> pizda;
    huitttta.clear();
    for (int i = 0; i < mid; i++) {
      while (pizda.size() && pizda.back() > a[i]) {
        pizda.pop_back();
      }
      pizda.push_back(a[i]);
    }
    huitttta.push_back(pizda.front());
    bool ok = true;
    for (int i = mid; i < n; i++) {
      if (a[i - mid] == pizda.front()) {
        pizda.pop_front();
      }
      while (pizda.size() && pizda.back() > a[i]) {
        pizda.pop_back();
      }
      pizda.push_back(a[i]);
      huitttta.push_back(pizda.front());
    }
    sort(ALL(huitttta));
    pp.resize(huitttta.size());
    iota(ALL(pp), 1);
    if (pp == huitttta) {
      r = mid;
    } else {
      l = mid;
    }
  }
  for (int i = 1; i < l; i++) {
    huyans[i] = '0';
  }
  cout << huyans << '\n';
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    run();
  }
  return 0;
}

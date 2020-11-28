//
// Created by watemus on 06.11.2020.
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

const int mod = 1e9 + 7;
int cr[10] = {2, 3, 5, 7, 11, 13};
vec<pair<int, int>> d;
int cnt = 0;
void rec() {
  if (d.size() > 8)
    return;
  if (d.size() == 8) {
    set<int> st{cr, cr + 6};
    if (st.size() == 1) {
      cout << d.size() << '\n';
      for (auto el : d) {
        cout << el.first << ' ' << el.second << '\n';
      }
      exit(0);
    }
  }
  if (d.size() == 7) cout << ++cnt << endl;
  for (int i = 0; i < 6; i++) {
    for (int j = i + 1; j < 6; j++) {
      int a = cr[i];
      int b = cr[j];
      cr[i] = cr[j] = a * b % mod;
      d.emplace_back(i + 1, j + 1);
      rec();
      cr[i] = a;
      cr[j] = b;
      d.pop_back();
    }
  }
}

void run() {
  rec();
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



//
// Created by watemus on 04.07.2020.
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

void run();

void run() {
  vec<pair<ll, ll>> a(3);
  for (int i : {0, 1, 2}) {
    cin >> a[i].first;
    a[i].second = i + 1;
  }
  sort(ALL(a));
  cout << "First" << endl;
  ll at;
  ll val = a[2].first * 2 - a[0].first - a[1].first;
  do {
    cout << val << endl;
    cin >> at;
    if (at == -1)
      return;
    if (at == a[2].second) {
      a[2].first += val;
      val = a[2].first * 2 - a[0].first - a[1].first;
      continue;
    } else {
      for (int i = 0; i < 3; i++) {
        if (a[i].second == at) {
          at = i;
          break;
        }
      }
      val = a[2].first - a[1 - at].first;
      cout << val << endl;
      cin >> at;
      if (at == 0)
        return;
      else
        exit(0);
    }
  } while (at == a[2].second);
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

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


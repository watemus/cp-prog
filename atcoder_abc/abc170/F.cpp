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

void run() {
  ll h, w, k;
  cin >> h >> w >> k;
  ll x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  vec<vec<char>> field(h + 2, vec<char>(w + 2, '@'));
  for (ll i = 1; i <= h; i++) {
    for (ll j = 1; j <= w; j++) {
      cin >> field[i][j];
    }
  }
  vec<vec<vec<ll>>> dist(h + 2, vec<vec<ll>>(w + 2, vec<ll>(4, INFL)));
  set<tuple<ll, ll, ll, ll>> st;
  for (ll i = 0; i < 4; i++) {
    st.emplace(0, x1, y1, i);
  }
  while (st.size()) {
    auto [cur_dist, x, y, dir] = *st.begin();
    st.erase(st.begin());
    if (cur_dist >= dist[x][y][dir]) continue;
    dist[x][y][dir] = cur_dist;
    if (field[x + DD[dir].first][y + DD[dir].second] == '.') {
      st.emplace(cur_dist + 1, x + DD[dir].first, y + DD[dir].second, dir);
    }
    for (ll chg_dir = 0; chg_dir < 4; chg_dir++) {
      if (dir == chg_dir) continue;
      if (field[x + DD[chg_dir].first][y + DD[chg_dir].second] == '.') {
        st.emplace((cur_dist + k - 1) / k * k + 1, x + DD[chg_dir].first, y + DD[chg_dir].second, chg_dir);
      }
    }
  }
  ll ans = INFL;
  for (int dir = 0; dir < 4; dir++) {
    ans = min(ans, dist[x2][y2][dir]);
  }
  cout << (ans == INFL ? -1 : (ans + k - 1) / k) << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

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


//
// Created by watemus on 28.06.2020.
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
    int n, k;
    cin >> n >> k;
    vec<int> a(n), b(n), t(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> a[i] >> b[i];
    vec<pair<int, int>> all, bob, alice;
    for (int i = 0; i < n; i++) {
      if (a[i] && b[i]) {
        all.emplace_back(t[i], i);
      }
      else if (a[i]) {
        alice.emplace_back(t[i], i);
      }
      else if (b[i]) {
        bob.emplace_back(t[i], i);
      }
    }
    sort(ALL(all));
    sort(ALL(alice));
    sort(ALL(bob));
    vec<int> pref1(min(bob.size(), alice.size()) + 1), pref2(all.size() + 1);
    if (pref1.size() + pref2.size() - 2 < k) {
      cout << "-1\n";
      return;
    }
    for (int i = 1; i < pref1.size(); i++) {
      pref1[i] = pref1[i - 1] + alice[i - 1].first + bob[i - 1].first;
    }
    for (int i = 1; i < pref2.size(); i++) {
      pref2[i] = pref2[i - 1] + all[i - 1].first;
    }
    int ans = INFL;
    for (int i = 0; i < min((int)pref1.size(), k + 1); i++) {
      if (pref2.size() > k - i)
        ans = min(ans, pref1[i] + pref2[k - i]);
    }
    cout << ans << '\n';
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
    cout << std::fixed << std::setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


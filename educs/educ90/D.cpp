//
// Created by watemus on 25.06.2020.
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
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename T1, typename T2>
using umap = unordered_map<T1, T2>;

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n;
    cin >> n;
    vec<int> a(n + 1), p1(n + 1), p2(n + 1);
    int mn1 = -INFL, mn2 = 0;
    int ans = 0;
    int cans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i % 2) {
            cans += a[i];
            p2[i] = p2[i - 1] + a[i];
            if (mn1 - p2[i] >= ans) {
                ans = mn1 - p2[i];
            }
            mn1 = max(mn1, p2[i]);
        } else {
            p2[i] = p2[i - 1] - a[i];
            if (mn2 - p2[i] >= ans) {
                ans = mn2 - p2[i];
            }
            mn2 = max(mn2, p2[i]);
        }
    }
    ans += cans;
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
    cout << fixed << setprecision(20);
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


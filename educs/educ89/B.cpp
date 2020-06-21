//
// Created by watemus on 11.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second

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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n, x, m;
    cin >> n >> x >> m;
    vector<pair<int, int>> segs{{x, x}};
    for (int i = 0; i < m; i++) {
        int lb, rb;
        cin >> lb >> rb;
        for (auto [lt, rt] : segs) {
            if (max(lt, lb) <= min(rb, rt)) {
                segs.emplace_back(lb, rb);
                break;
            }
        }
    }
    vector<pair<int, int>> scan;
    for (auto [lb, rb] : segs) {
        scan.emplace_back(lb, -1);
        scan.emplace_back(rb, 1);
    }
    sort(all(scan));
    int lvl = 1;
    int ans = 1;
    for (int i = 1; i < scan.size(); i++) {
        if (lvl > 0) {
            ans += scan[i].first - scan[i - 1].first;
        }
        if (scan[i].second == -1) {
            lvl++;
            if (lvl == 1) ans++;
        } else {
            lvl--;
        }
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
    cout << fixed << setprecision(20);
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


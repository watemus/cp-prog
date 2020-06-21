//
// Created by watemus on 17.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

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
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n, m;
    cin >> n >> m;
    vec<int> t(m);
    int mx = 0;
    for (int i = 0; i < m; i++) {
        cin >> t[i];
        mx = max(mx, t[i]);
    }
    cout << n * mx << '\n';
    vec<set<int>> sts(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sts[i].insert(j * mx);
        }
    }
    vec<vec<int>> ans(n, vec<int>(m));
    for (int i = 0; i < n; i++) {
        set<int> cr;
        for (int j = 0; j < m; j++) {
            ans[i][j] = (i + j) % n * mx;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << '\n';
        vec<pair<int, int>> cans;
        for (int j = 0; j < m; j++) {
            cans.emplace_back(ans[i][j], j + 1);
        }
        sort(all(cans));
        for (auto [x, y] : cans) {
            cout << y << ' ' << x << '\n';
        }
    }
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


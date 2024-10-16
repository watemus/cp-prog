//
// Created by watemus on 18.06.2020.
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
    vec<vec<int>> g(n), rg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    vec<int> clr(n);
    for (int i = 0; i < n; i++) {
        vec<int> cnt = {0, 0, 0};
        for (auto u : rg[i]) {
            cnt[clr[u]]++;
        }
        if (!cnt[0] && !cnt[1]) {
            clr[i] = 0;
        }
        else if (cnt[0] && !cnt[1]) {
            clr[i] = 1;
        }
        else if (cnt[1]) {
            clr[i] = 2;
        }
    }
    vec<int> ans;
    for (int i = 0; i < n; i++) {
        if (clr[i] == 2) ans.push_back(i + 1);
    }
    cout << ans.size() << '\n';
    for (auto v : ans) {
        cout << v << ' ';
    }
    cout << '\n';
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


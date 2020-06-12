//
// Created by watemus on 12.06.2020.
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

const int MAXN = 1e5;

vec<pair<int, int>> g[MAXN];
int ans[MAXN];
int usd[MAXN];
int cnt_edges = 1;

void dfs(int v) {
    usd[v] = 1;
    int cnt = 0;
    for (auto pr : g[v]) {
        int u = pr.first;
        int e = pr.second;
        if (!usd[u]) {
            ans[e] = cnt_edges++;
            dfs(u);
            cnt++;
        }
    }
    if (cnt == 0) {
        for (auto pr : g[v]) {
            int u = pr.first;
            int e = pr.second;
            if (ans[e] == -1) {
                ans[e] = cnt_edges++;
                break;
            }
        }
    }
}

void run() {
    int n, m;
    cin >> n >> m;
    if (n == 2) {
        cout << "1\n";
        return;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    int root = 0;
    int cnt_leaves = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 1) {
            root = i;
            cnt_leaves++;
            if (cnt_leaves > 1) {
                cout << "IMPOSSIBLE\n";
                return;
            }
        }
    }
    memset(ans, -1, sizeof ans);
    dfs(root);
    for (int i = 0; i < m; i++) {
        if (ans[i] == -1) {
            ans[i] = cnt_edges++;
        }
        cout << ans[i] << "\n";
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


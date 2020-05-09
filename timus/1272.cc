//
// Created by watemus on 17.04.2020.
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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n, -1), sz(n, 1) {}
    int get(int v) {
        if (p[v] == -1) return v;
        return p[v] = get(p[v]);
    }
    bool merge(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        p[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

void run() {
    int n, m, k;
    cin >> n >> m >> k;
    DSU d(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        d.merge(u, v);
    }
    int ans = 0;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        ans += d.merge(u, v);
    }
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
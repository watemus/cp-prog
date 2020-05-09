//
// Created by watemus on 03.05.2020.
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

constexpr int MAXN = 1e5 + 10;
constexpr int LOGN = 18;
constexpr int D = 12;

vector<int> g[MAXN];
int up[LOGN][MAXN], dep[MAXN];
int gg[D][D][MAXN];

void dfs(int v, int p) {
    up[0][v] = p;
    for (int i = 1; i < LOGN; i++) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (auto u : g[v]) {
        if (u == p) continue;
        dep[u] = dep[v] + 1;
        dfs(u, v);
    }
}

int anc(int v, int h) {
    for (int d = LOGN - 1; d >= 0; d--) {
        if ((1 << d) <= h) {
            h -= (1 << d);
            v = up[d][v];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = anc(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int d = LOGN - 1; d >= 0; d--) {
        if (up[d][v] != up[d][u]) {
            v = up[d][v];
            u = up[d][u];
        }
    }
    return up[0][v];
}

int usd_gg[D];
ll dp[1 << D];

void dfs_gg(int mv, int v) {
    usd_gg[v] = 1;
    for (int i = 0; i < g[mv].size(); i++) {
        if (gg[v][i][mv]) {
            if (usd_gg[i] == 1) {
                cout << "0\n";
                exit(0);
            } else if (!usd_gg[i]) {
                dfs_gg(mv, i);
            }
        }
    }
    usd_gg[v] = 2;
}

constexpr ll MOD = 1e9 + 7;
ll ans[MAXN];

void check(int v) {
    if (g[v].size() == 1 && v != 0) {
        ans[v] = 1;
        return;
    }
    memset(usd_gg, 0, sizeof usd_gg);
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] == up[0][v]) continue;
        if (!usd_gg[i]) dfs_gg(v, i);
    }
    int n = g[v].size();
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++) {
        if (g[v][i] == up[0][v]) continue;
        dp[1 << i] = 1;
    }
    int bd = INFI;
    for (int i = 0; i < n; i++) {
        if (g[v][i] == up[0][v]) {
            bd = i;
            break;
        }
    }
    for (int mask = 1; mask < (1 << n); mask++) {
        if (bd != INFI && (mask & (1 << bd))) continue;
        for (int i = 0; i < n; i++) {
            if (i == bd || ((1 << i) & mask)) continue;
            bool f = false;
            for (int j = 0; j < n; j++) {
                if (gg[i][j][v] && ((1 << j) & mask)) {
                    f = true;
                    break;
                }
            }
            if (f) continue;
            dp[mask + (1 << i)] += dp[mask];
            dp[mask + (1 << i)] %= MOD;
        }
    }
    if (bd == INFI) {
        ans[v] = dp[(1 << n) - 1];
    } else
        ans[v] = dp[(1 << n) - 1 - (1 << bd)];
    for (int i = 0; i < n; i++) {
        if (i == bd) continue;
        ans[v] = (ll(ans[v]) * ll(ans[g[v][i]])) % ll(MOD);
    }
}

void dfs2(int v, int p) {
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs2(u, v);
    }
    check(v);
}

void run() {
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            memset(gg[i][j], 0, sizeof gg[i][j]);
        }
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[0] = 0;
    dfs(0, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        int lc = lca(u, v);
        if (lc == v) {
            cout << "0\n";
            return;
        }
        if (lc == u) continue;
        int iu = 0, iv = 0;
        int uu = anc(u, dep[u] - dep[lc] - 1);
        int vv = anc(v, dep[v] - dep[lc] - 1);
        for (int j = 0; j < g[lc].size(); j++) {
            if (g[lc][j] == uu) iu = j;
            if (g[lc][j] == vv) iv = j;
        }
        gg[iv][iu][lc] = 1;
    }
    dfs2(0, 0);
    cout << ans[0] << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
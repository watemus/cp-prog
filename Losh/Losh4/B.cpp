//
// Created by watemus on 11.06.2020.
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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1e5 + 10;

vec<pair<int, int>> g[MAXN];
vec<pair<int, int>> gt[MAXN];
int tin[MAXN], tup[MAXN], usd[MAXN], tout[MAXN];
pair<int, int> edges[MAXN];
int is_bridge[MAXN];
int comp[MAXN];
int pv[MAXN], pe[MAXN];
int dep[MAXN];

int dfs_timer = 1;

void find_bridges(int v, int p) {
    tin[v] = tup[v] = dfs_timer++;
    usd[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;
        int e = g[v][i].second;
        if (e == p) continue;
        if (usd[u]) {
            tup[v] = min(tup[v], tin[u]);
        } else {
            find_bridges(u, e);
            if (tup[u] > tin[v]) {
                is_bridge[e] = 1;
            }
            tup[v] = min(tup[u], tup[v]);
        }
    }
    tout[v] = dfs_timer++;
}

void color(int v, int cl) {
    comp[v] = cl;
    usd[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;
        int e = g[v][i].second;
        if (is_bridge[e] && comp[u] != -1) {
            gt[comp[u]].emplace_back(comp[v], e);
            gt[comp[v]].emplace_back(comp[u], e);
        }
        if (is_bridge[e]) continue;
        if (usd[u]) continue;
        color(u, cl);
    }
}

void make_tree(int v) {
    usd[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        int u = g[v][i].first;
        int e = g[v][i].second;
        if (is_bridge[e]) {
            gt[comp[v]].emplace_back(comp[u], e);
        }
        if (!usd[u])
            make_tree(u);
    }
}

const int LOGN = 17;

int lup[LOGN][MAXN];

void dfs_tree(int v, int p) {
    tin[v] = dfs_timer++;
    usd[v] = 1;
    pv[v] = p;
    lup[0][v] = p;
    for (int i = 1; i < LOGN; i++) {
        lup[i][v] = lup[i - 1][lup[i - 1][v]];
    }
    for (int i = 0; i < gt[v].size(); i++) {
        int u = gt[v][i].first;
        int e = gt[v][i].second;
        if (u != p) {
            pe[u] = e;
            dep[u] = dep[v] + 1;
            dfs_tree(u, v);
        }
    }
    tout[v] = dfs_timer++;
}




char ans[MAXN];
int up[MAXN], down[MAXN];


bool is_anc(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (!is_anc(lup[i][u], v)) {
            u = lup[i][u];
        }
    }
    return pv[u];
}

void set_ans(int v, int p) {
    usd[v] = 1;
    for (auto [u, e] : gt[v]) {
        if (e == p) continue;
        set_ans(u, e);
        down[v] = max(down[v], down[u] - 1);
        up[v] = max(up[v], up[u] - 1);
    }
    if (p != -1) {
        if (up[v] && down[v]) {
            ans[p] = 'B';
        } else if (up[v]) {
            if (pv[comp[edges[p].first]] == comp[edges[p].second]) {
                ans[p] = 'R';
            } else {
                ans[p] = 'L';
            }
        } else if (down[v]) {
            if (pv[comp[edges[p].first]] == comp[edges[p].second]) {
                ans[p] = 'L';
            } else {
                ans[p] = 'R';
            }
        } else if (is_bridge[p]) {
            ans[p] = 'B';
        }
    }
}

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        edges[i] = {u, v};
    }
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < n; i++) {
        if (!usd[i]) find_bridges(i, -1);
    }
    memset(usd, 0, sizeof usd);
    memset(comp, -1, sizeof comp);
    int cl = 0;
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            color(i, cl);
            cl++;
        }
    }
    memset(usd, 0, sizeof ans);
    for (int i = 0; i < cl; i++) {
        if (!usd[i]) {
            dep[i] = 0;
            dfs_tree(i, i);
        }
    }
    memset(ans, '*', sizeof ans);
    for (int i = 0; i < m; i++) {
        if (!is_bridge[i]) {
            ans[i] = 'B';
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        u = comp[u];
        v = comp[v];
        int lc = lca(u, v);
        up[u] = max(up[u], dep[u] - dep[lc]);
        down[v] = max(down[v], dep[v] - dep[lc]);
    }
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < cl; i++) {
        if (!usd[i]) {
            set_ans(i, -1);
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i];
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


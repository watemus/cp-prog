//
// Created by watemus on 13.06.2020.
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 5e5 + 10;

vec<int> g[MAXN], rg[MAXN], go[MAXN];

int x[MAXN], y[MAXN];
int usd[MAXN];
int height[MAXN];
int comp[MAXN];
int up[MAXN], down[MAXN];

bool find_one(int v) {
    usd[v] = 1;
    if (x[v] == 0) {
        usd[v] = 2;
    }
    for (auto u : rg[v]) {
        if (usd[u] == 2) {
            usd[v] = 2;
        }
        if (!usd[u]) {
            find_one(u);
            if (usd[u] == 2) {
                usd[v] = 2;
            }
        }
    }
    return usd[v] == 2;
}

vec<int> tsort;

void make_tsort(int v) {
    usd[v] = 1;
    for (auto u : g[v]) {
        if (!usd[u]) make_tsort(u);
    }
    tsort.push_back(v);
}

void color(int v, int cl) {
    comp[v] = cl;
    usd[v] = 1;
    if (height[v] != -1) {
        if (up[comp[v]] == -1)
            up[comp[v]] = height[v];
        if (down[comp[v]] == -1) {
            down[comp[v]] = height[v];
        }
        up[comp[v]] = max(up[comp[v]], height[v]);
        down[comp[v]] = min(down[comp[v]], height[v]);
    }
    for (auto u : rg[v]) {
        if (!usd[u]) color(u, cl);
    }
}

void make_go(int v) {
    usd[v] = 1;
    for (auto u : g[v]) {
        if (!usd[u] && comp[u] == comp[v]) make_go(u);
    }
    for (auto u : g[v]) {
        if (!usd[u]) make_go(u);
        if (comp[u] != comp[v]) {
            go[comp[v]].push_back(comp[u]);
        }
    }
}

void make_ans(int v) {
    usd[v] = 1;
    for (auto u : go[v]) {
        if (!usd[u]) make_ans(u);
        if (down[u] != -1) {
            if (down[v] == -1) {
                down[v] = down[u];
            } else {
                down[v] = min(down[u], down[v]);
            }
        }
        if (up[u] != -1) {
            if (up[v] == -1) {
                up[v] = up[u];
            } else {
                up[v] = max(up[v], up[u]);
            }
        }
    }
}

void make_to(int v, vec<int> &to, int A) {
    if (x[v] == A) {
        to.push_back(v);
    }
    usd[v] = 1;
    for (auto u : g[v]) {
        if (!usd[u]) make_to(u, to, A);
    }
}

void run() {
    int A, B;
    int n, m;
    cin >> n >> m >> A >> B;
    vec<int> from, to;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        if (x[i] == 0) {
            from.push_back(i);
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, type;
        cin >> u >> v >> type;
        u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
        if (type == 2) {
            g[v].push_back(u);
            rg[u].push_back(v);
        }
    }
    memset(usd, 0, sizeof usd);
    for (auto v : from) {
        if (!usd[v]) {
            make_to(v, to, A);
        }
    }
    sort(all(to), [](int i, int j){
        return y[i] > y[j];
    });
    memset(usd, 0, sizeof usd);
    memset(height, -1, sizeof height);
    int h = 0;
    for (auto v : to) {
        height[v] = h++;
    }
    memset(usd, 0, sizeof usd);
    for (int v = 0; v < n; v++) {
        if (!usd[v]) make_tsort(v);
    }
    reverse(all(tsort));
    int cl = 0;
    memset(comp, -1, sizeof comp);
    memset(usd, 0, sizeof usd);
    memset(down, -1, sizeof down);
    memset(up, -1, sizeof up);
    for (auto u : tsort) {
        if (!usd[u]) {
            color(u, cl);
            cl++;
        }
    }
    memset(usd, 0, sizeof usd);
    for (int v = 0; v < n; v++) {
        if (!usd[v]) {
            make_go(v);
        }
    }
    memset(usd, 0, sizeof usd);
    for (int v = 0; v < cl; v++) {
        if (!usd[v]) {
            make_ans(v);
        }
    }
    sort(all(from), [](int i, int j){
        return y[i] > y[j];
    });
    bool checked = false;
    for (auto v : from) {
        if (up[comp[v]] == -1) {
            cout << 0 << '\n';
        } else {
            checked = true;
            cout << up[comp[v]] - down[comp[v]] + 1 << '\n';
            assert(down[comp[v]] <= up[comp[v]]);
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


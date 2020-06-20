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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 2e5;

vec<vec<int>> g, rg;
vec<int> st, usd;

int t[MAXN * 4];
int cnt[MAXN * 4];
int n;

void build(int v, int lb, int rb) {
    if (rb - lb == 1) {
        t[v] = lb;
    } else {
        int mid = (lb + rb) / 2;
        build(v * 2 + 1, lb, mid);
        build(v * 2 + 2, mid, rb);
        if (cnt[t[v * 2 + 1]] > cnt[t[v * 2 + 2]]) {
            t[v] = t[v * 2 + 1];
        } else {
            t[v] = t[v * 2 + 2];
        }
    }
}

void modify(int v, int lb, int rb, int at, int dt) {
    if (rb - lb == 1) {
        cnt[at] += dt;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid)
            modify(v * 2 + 1, lb, mid, at, dt);
        else
            modify(v * 2 + 2, mid, rb, at, dt);
        if (cnt[t[v * 2 + 1]] > cnt[t[v * 2 + 2]]) {
            t[v] = t[v * 2 + 1];
        } else {
            t[v] = t[v * 2 + 2];
        }
    }
}

void dfs(int v, int dep) {
    st.push_back(v);
    if (dep == 2) {
        cnt[st[2]]++;
    } else {
        for (auto u : g[v]) {
            dfs(u, dep + 1);
        }
    }
    st.pop_back();
}


void dfs_down(int v, int dep) {
    st.push_back(v);
    if (dep == 2) {
        {
            modify(0, 0, n, st[2], -1);
        }
    } else {
        for (auto u : g[v]) {
            if (!usd[u])
                dfs_down(u, dep + 1);
        }
    }
    st.pop_back();
}

void dfs_up(int v, int dep) {
    st.push_back(v);
    if (dep == 2) {
        {
            modify(0, 0, n, st[0], -1);
        }
    } else {
        for (auto u : rg[v]) {
            if (!usd[u])
                dfs_up(u, dep + 1);
        }
    }
    st.pop_back();
}

void run() {
    int m;
    cin >> n >> m;
    g.assign(n, {});
    rg.assign(n, {});
    usd.assign(n, 0);
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.insert({u, v});
    }
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        dfs(i, 0);
    }
    build(0, 0, n);
    vec<int> ans;
    while (cnt[t[0]] != 0) {
        int v = t[0];
        ans.push_back(v);
        dfs_down(v, 0);
        dfs_up(v, 0);
        for (auto u : g[v]) {
            if (usd[u]) continue;
            for (auto h : rg[v]) {
                if (usd[h]) continue;
                modify(0, 0, n, u, -1);
            }
        }
        usd[v] = 1;
    }
    cout << ans.size() << '\n';
    for (auto el : ans) {
        cout << el + 1 << ' ';
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


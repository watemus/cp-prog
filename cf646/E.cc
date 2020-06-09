//
// Created by watemus on 31.05.2020.
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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 2e5 + 10;
vector<int> g[MAXN];
const int LOGN = 19;
int up[LOGN][MAXN];
int a[MAXN], b[MAXN], c[MAXN], mn[MAXN], dep[MAXN];

multiset<int> cr;
vector<int> euler;

int  c1[MAXN], c2[MAXN];
int ANS = 0;
void dfs(int v, int p) {
    up[0][v] = p;
    euler.push_back(v);
    for (int i = 1; i < LOGN; i++) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    cr.insert(a[v]);
    mn[v] = *cr.begin();
    if (b[v] != c[v]) {
        if (b[v] == 0) c1[v]++;
        else c2[v]++;
    }
    for (auto u : g[v]) {
        if (u != p) {
            dep[u] = dep[v] + 1;
            dfs(u, v);
            c2[v] += c2[u];
            c1[v] += c1[u];
        }
    }
    int mnn = min(c1[v], c2[v]);
    ANS += mn[v] * mnn;
    c1[v] -= mnn, c2[v] -= mnn;
    cr.erase(cr.find(a[v]));
}

int pr(int v, int h) {
    for (int i = LOGN - 1; i >= 0; i--) {
        if (h >= (1 << i)) {
            h -= (1 << i);
            v = up[i][v];
        }
    }
    return v;
}

int lca(int u, int v) {
    if (dep[v] > dep[u]) swap(u, v);
    u = pr(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[i][v] != up[i][u]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][v];
}

void run() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[0] = 0;
    dfs(0, 0);
    if (c1[0] != c2[0]) {
        cout << "-1\n";
        return;
    }
    cout << ANS * 2 << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
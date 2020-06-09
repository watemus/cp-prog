//
// Created by watemus on 16.05.2020.
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

constexpr int MAXN = 1e5 + 10;

vector<pair<int, int>> g[MAXN];

int tin[MAXN], tup[MAXN], usd[MAXN], color_edges[MAXN], dif_colors[MAXN];
int cut_point[MAXN];


void find_cut_points(int v, int p) {
    static int dfs_timer = 1;
    tin[v] = tup[v] = dfs_timer++;
    usd[v] = 1;
    int cnt_p = 0;
    for (auto [u, id] : g[v]) {
        if (u == p) continue;
        if (usd[u]) {
            tup[v] = min(tup[v], tin[u]);
        } else {
            find_cut_points(u, v);
            cnt_p++;
            if (tup[u] >= tin[v] && p != -1) {
                cut_point[v] = 1;
            }
            tup[v] = min(tup[v], tup[u]);
        }
    }
    if (p == -1 && cnt_p > 1) {
        cut_point[v] = 1;
    }
}

void color(int v, int _color) {
    usd[v] = 1;
    for (auto [u, id] : g[v]) {
        if (color_edges[id] == -1) {
            color_edges[id] = _color;
            if (!usd[u] && !cut_point[u]) {
                color(u, _color);
            }
        }
    }
}

void color_from_cut_point(int v) {
    static int _color = 1;
    usd[v] = 1;
    set<int> colors;
    for (auto [u, id] : g[v]) {
        if (color_edges[id] == -1) {
            color_edges[id] = _color;
            if (!usd[u] && !cut_point[u]) {
                color(u, _color);
            }
            _color++;
        }
        colors.insert(color_edges[id]);
    }
    dif_colors[v] = colors.size();
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
    }
    memset(cut_point, 0, sizeof cut_point);
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            find_cut_points(i, -1);
        }
    }
    memset(usd, 0, sizeof usd);
    memset(color_edges, -1, sizeof color_edges);
    for (int i = 0; i < n; i++) {
        if (cut_point[i]) {
            color_from_cut_point(i);
        }
    }
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (dif_colors[i] > dif_colors[ans]) ans = i;
    }
    cout << ans + 1 << '\n';
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
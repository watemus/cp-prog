//
// Created by watemus on 27.03.2020.
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

const int MAXN = 5e5;

vector<int> g[MAXN];

int tin[MAXN], tout[MAXN], pr[MAXN];
int dfs_timer = 0;

void dfs(int v, int p) {
    tin[v] = dfs_timer++;
    pr[v] = p;
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    tout[v] = dfs_timer++;
}

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    for (int iter = 0; iter < m; iter++) {
        int k;
        cin >> k;
        vector<int> c(k);
        for (int i = 0; i < k; i++) {
            cin >> c[i];
            c[i]--;
            c[i] = pr[c[i]];
        }
        sort(all(c), [](auto a, auto b){
            return tin[a] < tin[b];
        });
        bool checked = true;
        for (int i = 0; i < k - 1; i++) {
            if (!(tin[c[i]] <= tin[c[i + 1]] && tout[c[i + 1]] <= tout[c[i]])) {
                checked = false;
                break;
            }
        }
        puts(checked ? "YES" : "NO");
    }
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
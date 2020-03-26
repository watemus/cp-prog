//
// Created by watemus on 26.03.2020.
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
int p[MAXN], dep[MAXN], tin[MAXN], tout[MAXN];

int dfs_timer = 0;

void dfs(int v, int pr) {
    tin[v] = dfs_timer++;
    for (auto u : g[v]) {
        if (u != pr) {
            p[u] =v;
            dep[u] = dep[v] + 1;
            dfs(u, v);
        }
    }
    tout[v] = dfs_timer++;
}

int vs[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[0] = 0;
    p[0] = 0;
    dfs(0, 0);
    vector<int> cnt(n);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int dp = -1;
        for (int j = 0; j < k; j++) {
            auto &el = vs[j];
            cin >> el;
            el--;
            if (dp == -1 || dep[el] > dep[dp]) {
                dp = el;
            }
        }
        int cur = 1;
        sort(vs, vs + k, [](auto a, auto b){
            return dep[a] < dep[b];
        });
        for (int j = 0; j < k - 1; j++) {
            if (tin[p[vs[j]]] <= tin[p[vs[j + 1]]] && tout[p[vs[j + 1]]] <= tout[p[vs[j]]]) {
                cur++;
            }
        }
        //cur += cnt[0];
        if (cur == k) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
//
// Created by watemus on 15.04.2020.
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

const int MAXN = 3e5;

vector<int> g[MAXN];
int pr[MAXN], cnt[MAXN], dep[MAXN], sz[MAXN], kk[MAXN];

void dfs(int v, int p) {
    pr[v] = p;
    sz[v] = 1;
    cnt[v] = 0;
    for (auto u : g[v]) {
        if (u != p) {
            dep[u] = dep[v] + 1;
            dfs(u, v);
            sz[v] += sz[u];
            cnt[v] += cnt[u] + sz[u];
        }
    }
    kk[v] = dep[v] - sz[v] + 1;
}

void run() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dep[0] = 0;
    dfs(0, -1);
    sort(kk, kk + n);
    reverse(kk, kk + n);
    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans += kk[i];
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
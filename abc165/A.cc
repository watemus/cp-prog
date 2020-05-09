//
// Created by watemus on 02.05.2020.
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

const int MAXN = 2e5 + 10;

int a[MAXN], ans[MAXN];
vector<int> g[MAXN];
int dp[MAXN];

void dfs(int v, int p) {
    ans[v] = ans[p];
    int idx = lower_bound(dp, dp + MAXN, a[v]) - dp;
    int prev_val = dp[idx];
    if (idx > ans[v]) {
        ans[v] = idx;
    }
    dp[idx] = min(dp[idx], a[v]);
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    dp[idx] = prev_val;
}

void run() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    fill(dp, dp + MAXN, INFL);
    dp[0] = 0;
    dp[1] = a[0];
    ans[0] = 1;
    for (auto u : g[0]) {
        dfs(u, 0);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
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
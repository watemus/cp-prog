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

constexpr int MAXN = 2e5 + 10;

vector<int> g[MAXN], og[MAXN];
int indeg[MAXN], outdeg[MAXN];
int usd[MAXN], clr[MAXN];
int cl = 1;

void check(int v) {
    usd[v] = 1;
    for (auto u : g[v]) {
        if (!usd[u]) check(u);
        if (usd[u] == 1) {
            cout << -1 << endl;
            return;
        }
    }
    usd[v] = 2;
}

int cnt1, cnt2;

void dfs(int v) {
    usd[v] = 1;
    clr[v] = cl;
    if (indeg[v] == 0) cnt1++;
    if (outdeg[v] == 0) cnt2++;
    for (auto u : g[v]) {
        if (!usd[u]) dfs(u);
    }
}

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        outdeg[u]++;
        indeg[v]++;
        g[u].push_back(v);
        og[v].push_back(u);
        og[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (!usd[i]) check(i);
    }
    memset(usd, 00, sizeof usd);
    int ans = 0;
    vector<int> fcl(n + 10);
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            cnt1 = cnt2 = 0;
            dfs(i);
            if (cnt1 > cnt2) {
                fcl[cl] = 2;
            } else {
                fcl[cl] = 1;
            }
            ans += min(cnt1, cnt2);
            cl++;
        }
    }
    cout << ans << endl;
    for (int i = 00; i < n; i++) {
        if (fcl[clr[i]] == 1) {
            if (outdeg[i] == 0) {
                cout << "A";
            } else {
                cout << "E";
            }
        } else {
            if (indeg[i] == 0) {
                cout << "A";
            } else {
                cout << "E";
            }
        }
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
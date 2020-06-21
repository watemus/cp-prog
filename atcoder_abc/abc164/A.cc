//
// Created by watemus on 01.05.2020.
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

const int MAX = 55;

void run() {
    int n, m, S;
    cin >> n >> m >> S;
    S = min(S, m * MAX - 1);
    vector<vector<pair<int, int>>> g(n * m * MAX);
    vector<vector<int>> c(n, vector<int>(m * MAX));
    vector<pair<int, int>> rc(n * m * MAX);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m * MAX; j++) {
            c[i][j] = cnt;
            rc[cnt] = {i, j};
            cnt++;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, cost, tm;
        cin >> u >> v >> cost >> tm;
        u--; v--;
        for (int j = cost; j < m * MAX; j++) {
            g[c[u][j]].emplace_back(c[v][j - cost], tm);
            g[c[v][j]].emplace_back(c[u][j - cost], tm);
        }
    }
    for (int i = 0; i < n; i++) {
        int cs, tm;
        cin >> cs >> tm;
        for (int j = 0; j + cs < m * MAX; ++j) {
            g[c[i][j]].emplace_back(c[i][j + cs], tm);
        }
    }
    set<pair<int, int>> st;
    vector<int> usd(n * m * MAX, INFL), u(n * m * MAX);
    vector<int> dist(n, INFL);
    usd[S] = 0;
    st.emplace(0, S);
    while (st.size()) {
        auto [dst, v] = *st.begin();
        st.erase(st.begin());
        if (u[v]) continue;
        u[v] =1;
        dist[rc[v].first] = min(dist[rc[v].first], dst);
        for (auto [u, cst] : g[v]) {
            if (usd[u] > dst + cst) {
                st.emplace(dst + cst, u);
                usd[u] = dst + cst;
            }
        }
    }
    for (int i = 1; i < n; i++) {
        cout << dist[i] << '\n';
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
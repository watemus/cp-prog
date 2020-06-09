//
// Created by watemus on 12.05.2020.
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


vector<vector<int>> c, a, cl;
vector<int> g, sz, st;
int n, m, t;

void dfs(int x, int y, int clr) {
    cl[x][y] = clr;
    sz[clr]++;
    st[clr] = a[x][y];
    if (a[x-1][y] == a[x][y] && !cl[x-1][y]) dfs(x-1, y, clr);
    if (a[x+1][y] == a[x][y] && !cl[x+1][y]) dfs(x+1, y, clr);
    if (a[x][y-1] == a[x][y] && !cl[x][y-1]) dfs(x, y-1, clr);
    if (a[x][y+1] == a[x][y] && !cl[x][y+1]) dfs(x, y+1, clr);
}

void run() {
    cin >> n >> m >> t;
    c.resize(n+2, vector<int>(m+2));
    cl.resize(n+2, vector<int>(m+2, 0));
    a.resize(n+2, vector<int>(m+2, -1));
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            a[i][j] = ch - '0';
            c[i][j] = cnt++;
        }
    }
    int clr = 1;
    sz.resize(cnt + 10);
    st.resize(cnt+ 10);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!cl[i][j]) {
                dfs(i, j, clr);
                clr++;
            }
        }
    }
    vector<vector<int>> dist(n+2, vector<int>(m+2, -2));
    queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (sz[cl[i][j]] > 1) {
                dist[i][j] = 0;
                q.push({i, j});
            } else {
                dist[i][j] = -1;
            }
        }
    }
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        if (dist[x+1][y] == -1) {
            dist[x+1][y] = dist[x][y] + 1;
            q.push({x+1, y});
        }
        if (dist[x-1][y] == -1) {
            dist[x-1][y] = dist[x][y] + 1;
            q.push({x-1, y});
        }
        if (dist[x][y+1] == -1) {
            dist[x][y+1] = dist[x][y] + 1;
            q.push({x, y+1});
        }
        if (dist[x][y-1] == -1) {
            dist[x][y-1] = dist[x][y] + 1;
            q.push({x, y-1});
        }
    }
    for (int i = 0; i < t; i++) {
        int x,y, tm;
        cin >> x >> y >> tm;
        tm -= dist[x][y];
        if (dist[x][y] == -1) {
            cout << a[x][y] << '\n';
        } else if (tm <= 0) {
            cout << a[x][y] << '\n';
        } else {
            cout << (a[x][y] + tm) % 2 << '\n';
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
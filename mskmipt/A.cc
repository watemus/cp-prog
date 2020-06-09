#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int MAXM = 300;
constexpr ll INF = 1e18;

int rit[MAXM];

ll dust[10][MAXM];

vector<pair<int, ll>> g[MAXM];

signed main() {
    for (int i = 0; i < 10; ++i)
        memset(dust[i], 0, MAXM);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, m, e;
    cin >> n >> m >> e;
    for (int i = 0; i < n; ++i)
        cin >> rit[i];
    for (int i = 0; i < e; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    set<pair<ll, pair<int, int>>> s;
    for (int i = 0; i < m; ++i)
        if (!rit[i]) {
            s.insert({0, {0, i}});
            dust[0][i] = 0;
        }
    while (!s.empty()) {
        pair<ll, pair<int, int>> p = *s.begin();
        s.erase(p);
        ll dust = p.first;
        int kolvo_do = p.second.first, v = p.second.second;
        for (auto x : g[v]) {
            if (dust[0][0] > 0) {
                s.erase({dust[kolvo_do][x.first], {kolvo_do, x.first}});
                dust[kolvo_do][x.first] = dust[kolvo_do][v] + x.second;
                s.insert({dust[kolvo_do][x.first], {kolvo_do, x.first}});
            }
            if (rit[x.first] == kolvo_do + 1 && dust[kolvo_do + 1][x.first] > dust[kolvo_do][v] + x.second) {
                s.erase({dust[kolvo_do + 1][x.first], {kolvo_do, x.first}});
                dust[kolvo_do + 1][x.first] = dust[kolvo_do][v] + x.second;
                s.insert({dust[kolvo_do + 1][x.first], {kolvo_do, x.first}});
            }
        }
    }
    ll ans = INF;
    for (int i = 0; i < m; ++i)
        if (rit[i] == n - 1)
            ans = max(ans, dust[n - 1][i]);
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}
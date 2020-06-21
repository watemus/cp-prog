//
// Created by watemus on 04.06.2020.
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 6e5;

vector<int> g[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<pair<int, int>> colors(n);
    vector<int> ans;
    queue<int> q;
    vector<int> usd(n);
    for (int i = 0; i < n; i++) {
        cin >> colors[i].first;
        colors[i].second = i;
        if (colors[i].first == 1) {
            q.push(i);
            usd[i] = 1;
        }
    }
    vector<int> deg(n, 1);
    int cnt = 0;
    while (q.size()) {
        int v = q.front();
        q.pop();
        ans.push_back(v + 1);
        cnt++;
        if (deg[v] != colors[v].first) {
            cout <<"-1\n";
            return;
        }
        for (auto u : g[v]) {
            if (!usd[u]) {
                if (deg[u] <= deg[v] - 1) {
                    cout <<"-1\n";
                    return;
                }
                deg[u] = max(deg[u], deg[v] + 1);
                if (deg[u] == colors[u].first) {
                    q.push(u);
                    usd[u] = 1;
                }
            }
            if (deg[u] == deg[v]) {
                cout <<"-1\n";
                return;
            }
        }
    }
    if (cnt == n) {
        for (auto el : ans) {
            cout << el << ' ';
        }
    } else {
        cout <<"-1\n";
        return;
    }
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


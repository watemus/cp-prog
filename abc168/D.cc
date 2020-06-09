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

constexpr int MAXN = 2e5;

vector<int> g[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v), g[v].push_back(u);
    }
    vector<int> dist(n, -1), pr(n, -1);
    int cnt = 0;
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (q.size()) {
        cnt++;
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                pr[u] = v;
                q.push(u);
            }
        }
    }
    if (cnt != n) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i = 1; i < n; i++) {
            cout << pr[i] + 1 << '\n';
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
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

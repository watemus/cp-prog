//
// Created by watemus on 08.06.2020.
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

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename T1, typename T2>
using umap = unordered_map<T1, T2>;

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 110;

vec<int> g[MAXN];
int comp[MAXN];
int usd[MAXN];

void dfs(int v, int cl) {
    comp[v] = cl;
    usd[v] = 1;
    for (auto u : g[v]) {
        if (!usd[u]) dfs(u, cl);
    }
}

int to[MAXN][MAXN], dist[MAXN][MAXN];

void run() {
    int n;
    cin >> n;
    vec<int> a(n), b(n), ra(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        a[i]--;
        ra[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int clr = 1;
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            dfs(i, clr);
            clr++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (comp[i] != comp[ra[b[i]]]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + n, INFI);
    }
    for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
            to[i][j] = j;
            dist[i][j] = 1;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j || i == k || j == k) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    to[i][j] = to[i][k];
                }
            }
        }
    }
    vec<pair<int, int>> ans;
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) continue;
        int u = i;
        int v = ra[b[i]];
        swap(a[u], a[v]);
        ra[a[u]] = u;
        ra[a[v]] = v;
        usd[u] = usd[v] = 1;
        int pu = u;
        while (u != v) {
            ans.push_back({u + 1, to[u][v] + 1});
            pu = u;
            u = to[u][v];
        }
        v = i;
        u = pu;
        while (u != v) {
            ans.push_back({u + 1, to[u][v] + 1});
            pu = u;
            u = to[u][v];
        }
    }
    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x.first << ' ' << x.second << '\n';
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


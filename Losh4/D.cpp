//
// Created by watemus on 11.06.2020.
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

const int MAXN = 2e4 + 10;

vec<int> g[MAXN];
int c[MAXN];
int comp[MAXN];
int usd[MAXN];
int dp[MAXN][2];

void dfs(int v, int cl) {
    usd[v] = 1;
    comp[v] = cl;
    for (auto u : g[v]) {
        if (!usd[u])
            dfs(u, cl);
    }
}

bool check_acyclic(int v, int p) {
    usd[v] = 1;
    for (auto u : g[v]) {
        if (u == p) continue;
        if (usd[u]) return true;
        bool res = check_acyclic(u, v);
        if (res) return true;
    }
    return false;
}

void calcdp(int v, int p) {
    dp[v][0] = 0;
    dp[v][1] = c[v];
    for (auto u : g[v]) {
        if (u == p) continue;
        calcdp(u, v);
        dp[v][0] += dp[v][1];
        dp[v][1] += min(dp[u][1], dp[u][0]);
    }
}

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(comp, -1, sizeof comp);
    int cl = 0;
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            dfs(i, cl);
            cl++;
        }
    }
    vec<vec<int>> comps(cl);
    for (int i = 0; i < n; i++) {
        comps[comp[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i < comps.size(); i++) {
        int cans = INFL;
        int cnt = comps[i].size();
        if (comps[i].size() == 1) {
            ans += c[comps[i][0]];
            continue;
        }
        map<int, int> to;
        for (int j = 0; j < cnt; j++) {
            to[comps[i][j]] = j;
            usd[comps[i][j]] = 1;
        }
        bool is_cycle = check_acyclic(comps[i][0], -1);
        if (!is_cycle) {
            calcdp(i, -1);
            ans += min(dp[i][0], dp[i][1]);
            continue;
        }
        for (int mask = 0; mask < (1 << cnt); mask++) {
            if (__builtin_popcount(mask) > (cnt + 1) / 2) continue;
            vec<int> col(cnt);
            int kk = 0;
            for (int j = 0; j < cnt; j++) {
                if (mask & (1 << j)) {
                    kk++;
                    col[j] = 1;
                }
            }
            for (int v : comps[i]) {
                if (col[v]) continue;
                for (auto u : g[v]) {
                    if (col[to[u]]) {
                        kk++;
                        break;
                    }
                }
            }
            if (kk == cnt) {
                int vans = 0;
                for (auto v : comps[i]) {
                    if (col[to[v]])
                        vans += c[v];
                }
                cans = min(cans, vans);
            }
        }
        ans += cans;
    }
    cout << ans << '\n';
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


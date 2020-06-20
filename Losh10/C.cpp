//
// Created by watemus on 18.06.2020.
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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

struct Edge {
    int u;
    int v;
    int flow;
    int cap;
    int cost;
};

const int MAXN = 300;

vec<int> g[MAXN];

const int S = MAXN - 2;
const int T = MAXN - 1;

vec<Edge> E;

int add_edge(int u, int v) {
    g[u].push_back(E.size());
    E.push_back({u, v, 0, 1, 0});
    g[v].push_back(E.size());
    E.push_back({v, u, 0, 0, 0});
    return E.size() - 2;
}

int pot[MAXN];
int dist[MAXN], usd[MAXN], pr[MAXN];

void FB() {
    fill(pot, pot + MAXN, INFI);
    pot[S] = 0;
    for (int iter = 0; iter < MAXN; iter++) {
        for (int i = 0; i < E.size(); i++) {
            if (E[i].flow < E[i].cap && pot[E[i].v] > pot[E[i].u] + E[i].cost) {
                pot[E[i].v] = pot[E[i].u] + E[i].cost;
            }
        }
    }
}

bool dijkstra() {
    fill(dist, dist + MAXN, INFI);
    memset(usd, 0, sizeof usd);
    dist[S] = 0;
    pr[S] = -1;
    while (true) {
        int min_v = -1;
        int min_dist = INFI;
        for (int i = 0; i < MAXN; i++) {
            if (!usd[i] && dist[i] < min_dist) {
                min_v = i;
                min_dist = dist[i];
            }
        }
        if (min_v == -1)
            break;
        usd[min_v] = 1;
        for (int id : g[min_v]) {
            auto &e = E[id];
            if (!usd[e.v] && e.flow < e.cap) {
                int nw = e.cost + pot[e.v] - pot[e.u];
                if (dist[e.v] > dist[e.u] + nw) {
                    dist[e.v] = dist[e.u] + nw;
                    pr[e.v] = e.u;
                }
            }
        }
    }
    return dist[T] != INFI;
}

int par[MAXN][MAXN];

int mincost_maxflow() {
    FB();
    int ans = 0;
    while (dijkstra()) {
        int pushed = INFI;
        for (int v = T; v != S; v = pr[v]) {
            pushed = min(pushed, E[par[pr[v]][v]].cap);
        }
        for (int v = T; v != S; v = pr[v]) {
            E[par[pr[v]][v]].flow += pushed;
            E[par[pr[v]][v]^1].flow -= pushed;
            ans += pushed * E[par[pr[v]][v]].cost;
        }
        for (int i = 0; i < MAXN; i++) {
            pot[i] += dist[i];
        }
    }
    return ans;
}
int to[MAXN], from[MAXN];

void run() {
    int n, k;
    cin >> n >> k;
    string enc, ans;
    cin >> enc >> ans;
    int cnt_v = 0;
    int cnt_u = 100;
    for (auto ch = 'a'; ch <= 'z'; ch++) {
        to[ch] = cnt_v++;
        from[ch] = cnt_u++;
        par[S][to[ch]] = add_edge(S, to[ch]);
        par[to[ch]][S] = par[S][to[ch]] + 1;
        par[from[ch]][T] = add_edge(from[ch], T);
        par[T][from[ch]] = par[from[ch]][T] + 1;
    }
    for (auto ch = 'A'; ch <= 'Z'; ch++) {
        to[ch] = cnt_v++;
        from[ch] = cnt_u++;
        par[S][to[ch]] = add_edge(S, to[ch]);
        par[to[ch]][S] = par[S][to[ch]]+1;
        par[from[ch]][T] = add_edge(from[ch], T);
        par[T][from[ch]] = par[from[ch]][T]+1;
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 100; j < 200; j++) {
            par[i][j] = add_edge(i, j);
            par[j][i] = par[i][j] + 1;
        }
    }
    for (int i = 0; i < n; i++) {
        E[par[to[enc[i]]][from[ans[i]]]].cost--;
        E[par[to[enc[i]]][from[ans[i]]]^1].cost++;
    }
    int res = mincost_maxflow();
    map<char, char> cto;
    cout << -res << '\n';
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


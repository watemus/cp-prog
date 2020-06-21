//
// Created by watemus on 30.03.2020.
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

const int MAXN = 1000;

struct Edge {
    int u;
    int v;
    int f;
    int c;
    int w;
};

vector<Edge> E;
vector<int> g[MAXN];
int n, m;

void add_edge(int u, int v, int c) {
    g[u].push_back(E.size());
    E.push_back({u, v, 0, c, c});
    g[v].push_back(E.size());
    E.push_back({v, u, 0, 0, 0});
}

int dist[MAXN];
int q[MAXN];

bool bfs(int s, int t) {
    fill(dist, dist + n, INFL);
    dist[s] = 0;
    int qs = 1;
    int qf = 0;
    q[qf] = s;
    while (qf < qs) {
        int v = q[qf];
        qf++;
        for (auto id : g[v]) {
            auto &e = E[id];
            if (dist[v] + 1 < dist[e.v] && e.c - e.f > 0) {
                dist[e.v] = dist[v] + 1;
                q[qs++] = e.v;
            }
        }
    }
    return dist[t] != INFL;
}

int ptr[MAXN];

int dfs(int v, int t, int flow) {
    if (v == t) return flow;
    for (; ptr[v] < g[v].size(); ptr[v]++) {
        int id = g[v][ptr[v]];
        auto &e = E[id];
        if (e.c - e.f > 0 && dist[v] + 1 == dist[e.v]) {
            int pushed = dfs(e.v, t, min(flow, e.c - e.f));
            if (pushed != 0) {
                E[id].f += pushed;
                E[id^1].f -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        memset(ptr, 0, sizeof ptr);
        int pushed = 0;
        do {
            pushed = dfs(s, t, INFL);
            ans += pushed;
        } while (pushed != 0);
    }
    return ans;
}

void run() {
    int x;
    cin >> n >> m >> x;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--;
        v--;
        add_edge(u, v, c);
    }
    ld lb = 0;
    ld rb = 2'000'000;
    for (int iter = 0; iter < 100; iter++) {
        ld mid = (lb + rb) / 2;
        for (auto &e : E) {
            e.c = floor(ld(e.w) / mid);
            e.f = 0;
        }
        int flow = maxflow(0, n - 1);
        if (flow >= x) {
            lb = mid;
        } else {
            rb = mid;
        }
    }
    cout << fixed << setprecision(228);
    cout << lb * ld(x) << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
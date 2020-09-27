//
// Created by watemus on 21.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

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
const ld PI = acos(-1);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 605;
const int N = 300;

vec<int> g[MAXN];

struct Edge {
    int u;
    int v;
    int flow;
    int cap;
    int cost;
};

vec<Edge> E;

void add_edge(int u, int v, int cap, int cost) {
    g[u].push_back(E.size());
    E.push_back({u, v, 0, cap, cost});
    g[v].push_back(E.size());
    E.push_back({v, u, 0, 0, -cost});
}

int dist[MAXN], pot[MAXN];
int in_q[MAXN];

void Ford_Bellman(int S) {
    fill(pot, pot + MAXN, INFL);
    memset(in_q, 0, sizeof in_q);
    pot[S] = 0;
    queue<int> q;
    q.push(S);
    in_q[S] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_q[u] = 0;
        for (int id : g[u]) {
            auto &e = E[id];
            if (pot[e.v] > pot[e.u] + e.cost && e.flow < e.cap) {
                pot[e.v] = pot[e.u] + e.cost;
                if (!in_q[e.v]) {
                    q.push(e.v);
                    in_q[e.v] = 1;
                }
            }
        }
    }
}

int usd[MAXN], pr[MAXN];

bool Dijkstra(int S, int T) {
    fill(dist, dist + MAXN, INFL);
    memset(usd, 0, sizeof usd);
    dist[S] = 0;
    for (int iter = 0; iter < MAXN; iter++) {
        int u = -1;
        int min_dist = INFL;
        for (int i = 0; i < MAXN; i++) {
            if (!usd[i] && (u == -1 || dist[u] > dist[i])) {
                u = i;
                min_dist = dist[i];
            }
        }
        if (dist[u] == INFL) break;
        usd[u] = 1;
        for (auto id : g[u]) {
            auto &e = E[id];
            int w = e.cost + pot[e.u] - pot[e.v];
            if (dist[e.u] + w < dist[e.v] && e.flow < e.cap) {
                dist[e.v] = dist[e.u] + w;
                pr[e.v] = id;
            }
        }
    }
    return dist[T] != INFL;
}

int min_cost_max_flow(int S, int T) {
    int ans = 0;
    Ford_Bellman(S);
    while (Dijkstra(S, T)) {
        for (int i = 0; i < MAXN; i++) {
            pot[i] += dist[i];
        }
        int pushed = INFL;
        for (int v = T; v != S; v = E[pr[v]].u) {
            pushed = min(pushed, E[pr[v]].cap - E[pr[v]].flow);
        }
        for (int v = T; v != S; v = E[pr[v]].u) {
            E[pr[v]].flow += pushed;
            E[pr[v] ^ 1].flow -= pushed;
            ans += pushed * E[pr[v]].cost;
        }
    }
    return ans;
}

void run() {
    int n;
    cin >> n;
    int S = MAXN - 2;
    int T = MAXN - 1;
    for (int i = 0; i < n; i++) {
        add_edge(S, i, 1, 0);
        add_edge(i + N, T, 1, 0);
        for (int j = 0; j < n; j++) {
            int cost;
            cin >> cost;
            add_edge(i, j + N, 1, cost);
        }
    }
    int ans = min_cost_max_flow(S, T);
    assert(ans >= 0);
    cout << ans << '\n';
    for (auto &e : E) {
        if (e.u < N && e.v >= N && e.flow && e.v != S) {
            cout << e.u + 1 << ' ' << e.v - N + 1 << '\n';
        }
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


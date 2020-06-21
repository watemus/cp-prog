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

const int MAXN = 6005;
const int MAX = 1e5;

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

int q[MAX];
int in_q[MAXN];
int pot[MAXN];

void Ford_Bellman(int S) {
    fill(pot, pot + MAXN, INFL);
    memset(in_q, 0, sizeof in_q);
    pot[S] = 0;
    int qb = 0;
    int qe = 1;
    while (qb < qe) {
        int u = q[qb];
        qb++;
        for (int id : g[u]) {
            auto &e = E[id];
            if (pot[e.u] + e.cost < pot[e.v]) {
                pot[e.v] = pot[e.u] + e.cost;
                if (!in_q[e.v]) {
                    q[qe] = e.v;
                    qe++;
                }
            }
        }
    }
}

int dist[MAXN], usd[MAXN], pr[MAXN];

bool Dijkstra(int S, int T) {
    fill(dist, dist + MAXN, INFL);
    dist[S] = 0;
    memset(usd, 0, sizeof usd);
    for (int iter = 0; iter < MAXN; iter++) {
        int min_dist = INFL;
        int u = -1;
        for (int i = 0; i < MAXN; i++) {
            if (dist[i] < min_dist && !usd[i]) {
                u = i;
                min_dist = dist[i];
            }
        }
        if (u == -1)
            break;
        for (auto id : g[u]) {
            auto &e = E[id];
            int w = e.cost + pot[e.u] - pot[e.v];
            if (dist[e.u] + w < dist[e.v]) {
                dist[e.v] = dist[e.u] + w;
                pr[e.v] = id;
            }
        }
    }
    return dist[T] != INFL;
}

int min_cost(int S, int T) {
    Ford_Bellman(S);
    int ans = 0;
    for (int iter = 0; iter < 4; iter++) {
        bool has = Dijkstra(S, T);
        if (!has) return 1;
        for (int i = 0; i < MAXN; i++) {
            pot[i] += dist[i];
        }
        for ()
    }
}

void run() {
    int n;
    cin >> n;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
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


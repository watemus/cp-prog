//
// Created by watemus on 13.06.2020.
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
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 1e4;
vec<int> g[MAXN];

vec<int> q;

int ask(int a, int b) {
#ifdef LOCAL
    return q[a - 1] | q[b - 1];
#endif
    cout << "? " << a << ' ' << b << endl;
    int res;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}

struct Edge {
    int u;
    int v;
    int f;
    int c;
};

vec<Edge> E;

void add_edge(int u, int v) {
    g[u].push_back(E.size());
    E.push_back({u, v, 0, 1});
    g[v].push_back(E.size());
    E.push_back({v, u, 0, 0});
}

int n;

vec<int> dist;

bool bfs(int S, int T) {
    dist.assign(max(100LL, 3 * n), -1);
    dist[S] = 0;
    queue<int> q;
    q.push(S);
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (auto id : g[v]) {
            if (dist[E[id].v] == -1 && E[id].f < E[id].c) {
                dist[E[id].v] = dist[v] + 1;
                q.push(E[id].v);
            }
        }
    }
    return dist[T] != -1;
}

int ptr[MAXN];

int dfs(int v, int flow, int T) {
    if (flow == 0) return 0;
    if (v == T) return flow;
    for (; ptr[v] < g[v].size(); ptr[v]++) {
        int id = g[v][ptr[v]];
        if (dist[E[id].v] != dist[v] + 1) continue;
        int pushed = dfs(E[id].v, min(flow, E[id].c - E[id].f), T);
        if (pushed > 0) {
            E[id].f += pushed;
            E[id^1].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic(int S, int T) {
    int flow = 0;
    for (;;) {
        if (!bfs(S, T))  break;
        memset (ptr, 0, max(100LL, 3 * n) * sizeof ptr[0]);
        while (int pushed = dfs(S, INFI, T))
            flow += pushed;
    }
    return flow;
}


void run() {
    srand(time(NULL));
    cin >> n;
    vec<int> p(n);
    q.resize(n);
    iota(all(q), 0);
    iota(all(p), 0);
    random_shuffle(all(p));
    map<int, set<int>> masks;
    for (int i = 0; i < n; i++) {
        masks[i] = {};
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int ij = (i | j);
            masks[i].insert(ij);
            masks[j].insert(ij);
        }
    }
    vec<vec<int>> masks_p(n);
    int qrs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < min(n, i + 3); j++) {
            int res = ask(p[i] + 1, p[j] + 1);
            qrs++;
            masks_p[i].push_back(res);
            masks_p[j].push_back(res);
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == n - j - 1) continue;
            int res = ask(p[i] + 1, p[n - j - 1] + 1);
            qrs++;
            masks_p[i].push_back(res);
            masks_p[n - j - 1].push_back(res);
        }
    }
    for (int i = qrs + 1; i <= 4269; i++) {
        int u = rand() % n;
        int v = rand() % n;
        while (abs(u -v) <= 2) {
            u = rand() % n;
            v = rand() % n;
        }
        int res = ask(p[u] + 1, p[v] + 1);
        masks_p[u].push_back(res);
        masks_p[v].push_back(res);
    }
    int S = n * 2 + 5;
    int F = n * 2 + 6;
    for (int i = 0; i < n; i++) {
        add_edge(S, i);
        add_edge(n + i, F);
    }
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int num = 0; num < n; num++) {
            bool correct = true;
            for (auto mask : masks_p[i]) {
                if (!masks[num].count(mask)) {
                    correct = false;
                    break;
                }
            }
            if (correct) {
                cnt++;
            }
        }
        if (cnt > 1) {
            pq.push({cnt, i});
        }
    }
    while (pq.size()) {
        auto [c, pr] = pq.top();
        pq.pop();
        if (masks_p[pr].size() >= 4) continue;
        for (int i : {0, 1}) {
            int u = rand() % n;
            while (u == pr) {
                u = rand() % n;
            }
            int res = ask(p[u] + 1, p[pr] + 1);
            masks_p[pr].push_back(res);
            masks_p[u].push_back(res);
            qrs++;
            if (qrs == 4269) break;
        }
        if (qrs == 4269) break;
    }
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int num = 0; num < n; num++) {
            bool correct = true;
            for (auto mask : masks_p[i]) {
                if (!masks[num].count(mask)) {
                    correct = false;
                    break;
                }
            }
            if (correct) {
                add_edge(num, n + p[i]);
            }
        }
    }
    int flow = dinic(S, F);
    vec<int> ans(n);
    for (auto e : E) {
        if (e.f == 1 && e.u < n) {
            ans[e.v - n] = e.u;
        }
    }
    cout << "! ";
    for (auto el : ans) {
        cout << el << ' ';
    }
    cout << endl;
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    //std::freopen("input.txt", "r", stdin);
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


//
// Created by watemus on 19.06.2020.
//



#ifdef lolipop
#define _GLIBCXX_DEBUG
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#endif

/*
    This ain't a milly rock
    This a money dance
    And my D' ain't hard
    That's a thirty in my pants
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <ctime>
#include <map>
#include <random>
#include <iomanip>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <bitset>
#include <deque>
#include <utility>

using namespace std;

//#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double

inline void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

//mt19937 rnd(time(nullptr));

const int maxN = 3300 * 2;
const int inf = 1e9 + 123;

struct Edge {
    int a, b, c, flow = 0;
    int cost = 0;
    Edge(int _a, int _b, int _c, int _cost) : a(_a), b(_b), c(_c), cost(_cost){}
    Edge(){}
};


int N;
vector <Edge> E;
vector <int> g[maxN];
vector <int> d;
vector <int> p;
vector <int> inq;

inline void insertEdge(int a, int b, int c, int cost) {
    g[a].push_back((int) E.size());
    E.push_back(Edge(a, b, c, cost));
    g[b].push_back((int) E.size());
    E.push_back(Edge(b, a, 0, -cost));
}

int Q[maxN * 1000];

inline bool FordBellman(int s, int t) {
    /*d.assign(N, inf);
    p.assign(N, -1);
    d[s] = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < (int) E.size(); ++j) {
            Edge& e = E[j];
            if(e.a == inf || e.c - e.flow <= 0) continue;
            if(d[e.b] > d[e.a] + e.cost) {
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = j;
            }
        }
    }
    if(p[t] == -1) return false;
    return true;*/
    d.assign(N, inf);
    p.assign(N, -1);
    d[s] = 0;\
    inq[s] = 1;
    int qs = 0;
    int qf = 1;
    Q[qs] = 0;
    while (qs < qf) {
        int u = Q[qs];
        qs++;
        inq[u] = 0;
        for (auto to : g[u]) {
            Edge& e = E[to];
            if (e.c - e.flow > 0 && d[e.b] > d[e.a] + e.cost) {
                d[e.b] = d[e.a] + e.cost;
                p[e.b] = to;
                if (!inq[e.b]) {
                    inq[e.b] = true;
                    Q[qf++] = e.b;
                }
            }
        }
    }
    return d[t] != inf;
}

inline void go(int s, int t) {
    vector <int> path;
    while(p[t] != -1) {
        path.push_back(p[t]);
        t = E[p[t]].a;
    }
    int min_f = inf;
    for(auto i : path) {
        min_f = min(min_f, E[i].c - E[i].flow);
    }
    for(auto i : path) {
        E[i].flow += min_f;
        E[i^1].flow -= min_f;
    }
}

inline void mincost(int s, int t, int num) {
    int ind = 0;
    while(FordBellman(s, t)) {
        go(s, t);
        ind++;
        if (ind == num) break;
    }
}

inline int countcost() {
    int ret = 0;
    for(auto i : E) {
        ret += i.flow * i.cost;
    }
    return ret;
}

inline void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    int s = 0, t = 1;
    N = 2;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<int> numbegin(n, 0);
    vector<int> numend(n, 0);
    for (int i = 0; i < n; ++i) {
        numbegin[i] = N++;
        numend[i] = N++;
    }
    for (int i = 0; i < n; ++i) {
        insertEdge(s, numbegin[i], inf, 0);
        insertEdge(numbegin[i], numend[i], 1, 0);
        insertEdge(numend[i], t, 1, -1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int counter = 0;
            if (abs(v[i] - v[j]) == 1 || abs(v[i] - v[j]) % 7 == 0) {
                insertEdge(numend[i], numbegin[j], 1, -1);
                counter++;
                //                if (counter == 5) break;
                break;
            }
        }
    }
    inq.assign(N, 0);
    mincost(s, t, 4);
    cout << -1 * countcost() / 2 << '\n';
}

signed main() {
#ifdef lolipop
    freopen("input.txt", "r", stdin);
#else
    fastio();
#endif
    int T = 1;
    // cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
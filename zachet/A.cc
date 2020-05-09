//
// Created by watemus on 04.05.2020.
//

#ifdef LOCAL
//#define _GLIBCXX_DEBUG
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

#ifdef LOCAL
#else
#endif

const int MAX = 1e7;

struct Line {
    int k, b;
};

inline int apply(Line &ln, int val) {
    return ln.k * val + ln.b;
}

Line t[MAX];
int tl[MAX], tr[MAX];
int cnt = 0;
const int MAX_K = 2e5 + 10;

inline int new_node() {
    t[cnt] = {0, -INFL};
    return cnt++;
}

inline int cpy_node(int v) {
    int u = new_node();
    tl[u] = tl[v];
    tr[u] = tr[v];
    t[u] = t[v];
    return u;
}

void add_line(Line ln, int v, int lb, int rb) {
    int mid = (lb + rb) / 2;
    bool mid_cond = apply(ln, mid) > apply(t[v], mid);
    bool lb_cond = apply(ln, lb) > apply(t[v], lb);
    if (mid_cond) {
        swap(t[v], ln);
    }
    if (rb - lb > 1) {
        if (mid_cond != lb_cond) {
            if (tl[v] == -1) {
                tl[v] = new_node();
            } else {
                tl[v] = cpy_node(tl[v]);
            }
            add_line(ln, tl[v], lb, mid);
        } else {
            if (tr[v] == -1) {
                tr[v] = new_node();
            } else {
                tr[v] = cpy_node(tr[v]);
            }
            add_line(ln, tr[v], mid, rb);
        }
    }
}

int get_max(int v, int lb, int rb, int at) {
    int ans = apply(t[v], at);
    if (rb - lb == 1) return ans;
    int mid = (lb + rb) / 2;
    if (at < mid) {
        if (tl[v] == -1) return ans;
        ans = max(ans, get_max(tl[v], lb, mid, at));
    } else {
        if (tr[v] == -1) return ans;
        ans = max(ans, get_max(tr[v], mid, rb, at));
    }
    return ans;
}

void run() {
    memset(tl, -1, sizeof tl);
    memset(tr, -1, sizeof tr);
    int n, m;
    cin >> n >> m;
    vector<int> roots(n);
    for (int i = 0; i < n; i++) {
        roots[i] = new_node();
    }
    for (int i = 0; i < m; i++) {
        char q;
        cin >> q;
        if (q == '#') {
            int src, dst;
            cin >> src >> dst;
            src--; dst--;
            roots[dst] = cpy_node(roots[src]);
        } else if (q == '+') {
            int root, a, b;
            cin >> root >> a >> b;
            root--;
            add_line({b, -a}, roots[root], 0, MAX_K);
        } else {
            int root, k;
            cin >> root >> k;
            root--;
            cout << get_max(roots[root], 0, MAX_K, k) << '\n';
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
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
//
// Created by watemus on 03.05.2020.
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

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 1010;
constexpr int MAX = 1e6 + 10;

struct DSU {
    vector<int> pr, sz;
    DSU(int n) : pr(n, -1), sz(n, 1) {}
    int get(int v) {
        if (pr[v] == -1) return v;
        return pr[v] = get(pr[v]);
    }
    void merge(int u, int v) {
        u = get(u);
        v = get(v);
        if (sz[v] > sz[u]) swap(u, v);
        pr[v] = u;
        sz[u] += sz[v];
    }
};

struct E {
    int u;
    int v;
    int c;
};

void run() {
    int n, m;
    cin >> n >> m;
    vector<E> e(m);
    for (auto &[u, v, c] : e) {
        cin >> u >> v >> c;
        u--; v--;
    }
    stable_sort(all(e), [](auto a, auto b){
        return a.c < b.c;
    });
    vector<E> ans;
    DSU d(n);
    int sm = 0;
    for (auto edge : e) {
        if (d.get(edge.u) != d.get(edge.v)) {
            d.merge(edge.u, edge.v);
            ans.push_back(edge);
            sm += edge.c;
        }
    }
    if (d.sz[d.get(0)] != n) {
        cout << "-1\n";
        return;
    }
    int price_r, price_b;
    int cnt_r, cnt_b;
    cin >> price_r >> cnt_r;
    cin >> price_b >> cnt_b;
    if (price_r > price_b) {
        swap(price_r, price_b);
        swap(cnt_r, cnt_b);
    }
    bitset<MAX> r;
    r[0] = true;
    for (auto [u, v, c] : ans) {
        r |= r << c;
    }
    int ansik = INT64_MAX;
    for (int i = 0; i < min(MAX, cnt_r + 1); i++) {
        if (r[i]) {
            int cr = i;
            int cb = sm - i;
            if (cb <= cnt_b) {
                ansik = min(ansik, i * price_r + (sm - i) * price_b);
            }
        }
    }
    for (int i = 0; i < min(MAX, cnt_b + 1); i++) {
        if (r[i]) {
            int cr = i;
            int cb = sm - i;
            if (cb <= cnt_r) {
                ansik = min(ansik, i * price_b + (sm - i) * price_r);
            }
        }
    }
    cout << (ansik == INT64_MAX ? -1 : ansik) << '\n';
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
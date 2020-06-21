//
// Created by watemus on 30.04.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second

using ll = long long;
using ld = long double;
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
const int MAXN = 100;
#else
const int MAXN = 1e5;
#endif

struct segtree {
    ll t[MAXN * 4];
    segtree(int n, std::vector<int> &v) {
        build(0, 0, n, v);
    }
    void build(int v, int lb, int rb, std::vector<int> &arr) {
        if (rb - lb > 1) {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, arr);
            build(v * 2 + 2, mid, rb, arr);
            t[v] = std::min(t[v * 2 + 1], t[v * 2 + 2]);
        } else {
            t[v] = arr[lb];
        }
    }
    ll get(int v, int lb, int rb, int lt, int rt) {
        if (lt <= lb && rb <= rt) {
            return t[v];
        }
        ll ans = INFL;
        int mid = (lb + rb) / 2;
        if (lt < mid) {
            ans = std::min(ans, get(v * 2 + 1, lb, mid, lt, rt));
        }
        if (mid < rt) {
            ans = std::min(ans, get(v * 2 + 2, mid, rb, lt, rt));
        }
        return ans;
    }
    void update(int v, int lb, int rb, int at, ll new_val) {
        if (rb - lb == 1) {
            t[v] = new_val;
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid) {
                update(v * 2 + 1, lb, mid, at, new_val);
            } else {
                update(v * 2 + 2, mid, rb, at, new_val);
            }
            t[v] = std::min(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
};

void run() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    segtree st(n, v);
    for (int i = 0; i < m; i++) {
        int q;
        std::cin >> q;
        if (q == 1) {
            int at;
            ll new_val;
            std::cin >> at >> new_val;
            st.update(0, 0, n, at, new_val);
        } else {
            int lb, rb;
            std::cin >> lb >> rb;
            std::cout << st.get(0, 0, n, lb, rb) << '\n';
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
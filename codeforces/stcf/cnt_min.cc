//
// Created by watemus on 30.04.2020.
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
const int MAXN = 100;
#else
const int MAXN = 1e5;
#endif

struct segtree {
    pair<int, int> t[MAXN * 4];
    segtree(int n, vector<int> &arr) {
        build(0, 0, n, arr);
    }
    static pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
        if (a.first == b.first) {
            return {a.first, a.second + b.second};
        }
        return (a.first < b.first ? a : b);
    }
    void build(int v, int lb, int rb, vector<int> &arr) {
        if (rb - lb > 1) {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, arr);
            build(v * 2 + 2, mid, rb, arr);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        } else {
            t[v] = {arr[lb], 1};
        }
    }
    void update(int v, int lb, int rb, int at, int new_val) {
        if (rb - lb == 1) {
            t[v] = {new_val, 1};
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid)
                update(v * 2 + 1, lb, mid, at, new_val);
            else
                update(v * 2 + 2, mid, rb, at, new_val);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    pair<int, int> get(int v, int lb, int rb, int lt, int rt) {
        if (lt <= lb && rb <= rt) {
            return t[v];
        }
        pair<int, int> ans = {INFL, INFL};
        int mid = (lb + rb) / 2;
        if (lt < mid)
            ans = merge(ans, get(v * 2 + 1, lb, mid, lt, rt));
        if (mid < rt)
            ans = merge(ans, get(v * 2 + 2, mid, rb, lt, rt));
        return ans;
    }
};

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    segtree st(n, a);
    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        if (q == 1) {
            int at, val;
            cin >> at >> val;
            st.update(0, 0, n, at, val);
        } else {
            int lt, rt;
            cin >> lt >> rt;
            auto ans = st.get(0, 0, n, lt, rt);
            cout << ans.first << ' ' << ans.second << '\n';
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
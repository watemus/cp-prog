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

struct seg_info {
    int max = 0;
    int suf = 0;
    int pref = 0;
    int len = 0;
    int sum = 0;
    seg_info(int val)
    : len(1), sum(val) {
        if (val >= 0) {
            max = suf = pref = val;
        }
    }
    seg_info() = default;
};

seg_info merge(seg_info lhs, seg_info rhs) {
    seg_info res;
    res.len = lhs.len + rhs.len;
    res.sum = lhs.sum + rhs.sum;
    res.max = max({lhs.max, rhs.max, lhs.suf + rhs.pref});
    res.pref = lhs.pref;
    if (lhs.sum + rhs.pref > res.pref) {
        res.pref = lhs.sum + rhs.pref;
    }
    res.suf = rhs.suf;
    if (rhs.sum + lhs.suf > res.suf) {
        res.suf = rhs.sum + lhs.suf;
    }
    return res;
}

struct segtree {
    seg_info t[MAXN * 4];
    segtree(int n, vector<int> &arr) {
        build(0, 0, n, arr);
    }
    void build(int v, int lb, int rb, vector<int> &arr) {
        if (rb - lb > 1) {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, arr);
            build(v * 2 + 2, mid, rb, arr);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        } else {
            t[v] = seg_info(arr[lb]);
        }
    }
    void update(int v, int lb, int rb, int at, int new_val) {
        if (rb - lb == 1) {
            t[v] = seg_info(new_val);
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid)
                update(v * 2 + 1, lb, mid, at, new_val);
            else
                update(v * 2 + 2, mid, rb, at, new_val);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

};

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (auto &el : arr) cin >> el;
    segtree st(n, arr);
    cout << st.t[0].max << '\n';
    for (int i = 0; i < m; i++) {
        int at, new_val;
        cin >> at >> new_val;
        st.update(0, 0, n, at, new_val);
        cout << st.t[0].max << '\n';
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
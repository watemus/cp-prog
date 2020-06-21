//
// Created by watemus on 01.05.2020.
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
    int t[MAXN * 4];
    segtree(int n, vector<int> &arr) {
        build(0, 0, n, arr);
    }
    void build(int v, int lb, int rb, vector<int> &arr) {
        if (rb - lb > 1) {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, arr);
            build(v * 2 + 2, mid, rb, arr);
            t[v] = t[v * 2 + 1] + t[v * 2 + 2];
        } else {
            t[v] = arr[lb];
        }
    }
    void update(int v, int lb, int rb, int at, int new_val) {
        if (rb - lb == 1) {
            t[v] = new_val;
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid)
                update(v * 2 + 1, lb, mid, at, new_val);
            else
                update(v * 2 + 2, mid, rb, at, new_val);
            t[v] = t[v * 2 + 1] + t[v * 2 + 2];
        }
    }
    int get(int v, int lb, int rb, int k) {
        if (rb - lb == 1) {
            return lb;
        } else {
            int mid = (lb + rb) / 2;
            if (t[v * 2 + 1] >= k) {
                return get(v * 2 + 1, lb, mid, k);
            }
            k -= t[v * 2 + 1];
            return get(v * 2 + 2, mid, rb, k);
        }
    }

};

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    segtree st(n, arr);
    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        if (q == 1) {
            int at;
            cin >> at;
            int new_val = !arr[at];
            arr[at] = new_val;
            st.update(0, 0, n, at, new_val);
        } else {
            int k;
            cin >> k;
            cout << st.get(0, 0, n, k + 1) << '\n';
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
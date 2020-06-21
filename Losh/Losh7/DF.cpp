//
// Created by watemus on 15.06.2020.
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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
const int MAXN = 100;
#else
const int MAXN = 100;
#endif


struct segtree {
    int t[MAXN * 2 + 10];
    void build(int v, int lb, int rb, vec<int> &a) {
        if (rb - lb == 1) {
            t[v] = a[lb];
        } else {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, a);
            build(v * 2 + 2, mid, rb, a);
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    int get(int v, int lb, int rb, int ql, int qr, int val) {
        if (rb <= ql || lb >= qr || t[v] <= val)
            return -1;
        if (rb - lb == 1)
            return lb;
        int mid = (lb + rb) / 2;
        int ans = get(v * 2 + 1, lb, mid, ql, qr, val);
        if (ans == -1)
            ans = get(v * 2 + 2, mid, rb, ql, qr, val);
        return ans;
    }
    void modify(int v, int lb, int rb, int at, int new_val) {
        if (rb - lb == 1) {
            t[v] = new_val;
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid) {
                modify(v * 2 + 1, lb, mid, at, new_val);
            } else {
                modify(v * 2 + 2, mid, rb, at, new_val);
            }
            t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
};

void run() {
    int n, m;
    cin >> n >> m;
    vec<int> dep(n);
    for (int i = 0; i < n; i++) {
        cin >> dep[i];
    }
    segtree t;
    t.build(0, 0, n, dep);
    vec<int> vans(n);
    for (int i = 0; i < n; i++) {
        int to = t.get(0, 0, n, i, n, dep[i]);
        if (to != -1) {
            vans[to]++;
        }
    }
    segtree mx;
    mx.build(0, 0, n, vans);
    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        q--;
        if (q == -1) {
            cout << mx.t[0] << '\n';
        } else {
            int g1 = t.get(0, 0, n, q, n, dep[q]);
            int g2 = t.get(0, 0, n, q + 1, n, dep[q + 1]);
            if (g1 != -1) {
                vans[g1]--;
                mx.modify(0, 0, n, g1, vans[g1]);
            }
            if (g2 != -1) {
                vans[g2]--;
                mx.modify(0, 0, n, g2, vans[g2]);
            }
            t.modify(0, 0, n, q, dep[q + 1]);
            t.modify(0, 0, n, q + 1, dep[q]);
            mx.modify(0, 0, n, q, vans[q + 1]);
            mx.modify(0, 0, n, q + 1, vans[q]);
            swap(vans[q], vans[q + 1]);
            swap(dep[q], dep[q + 1]);
            g1 = t.get(0, 0, n, q, n, dep[q]);
            g2 = t.get(0, 0, n, q + 1, n, dep[q + 1]);
            if (g1 != -1) {
                vans[g1]++;
                mx.modify(0, 0, n, g1, vans[g1]);
            }
            if (g2 != -1) {
                vans[g2]++;
                mx.modify(0, 0, n, g2, vans[g2]);
            }
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


//
// Created by watemus on 19.04.2020.
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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif

constexpr int SIZE = 1e7;
constexpr int MAXN = 1e5 + 228;

int t[SIZE];
int lt[SIZE], rt[SIZE];
int arr[MAXN];
int cnt = 1;

int new_node() {
    return cnt++;
}

int cpy(int v) {
    int u = new_node();
    t[u] = t[v];
    lt[u] = lt[v];
    rt[u] = rt[v];
    return u;
}

int build(int lb, int rb) {
    int v = new_node();
    if (rb - lb == 1) {
        t[v] = arr[lb];
    } else {
        int mid = (lb + rb) >> 1;
        lt[v] = build(lb, mid);
        rt[v] = build(mid, rb);
        t[v] = t[lt[v]] + t[rt[v]];
    }
    return v;
}

int upd(int u, int tl, int tr, int at) {
    int v = cpy(u);
    if (tr - tl == 1) {
        t[v]++;
    } else {
        int mid = (tl + tr) / 2;
        if (at < mid) {
            lt[v] = upd(lt[v], tl, mid, at);
        } else {
            rt[v] = upd(rt[v], mid, tr, at);
        }
        t[v] = t[lt[v]] + t[rt[v]];
    }
    return v;
}

int get(int v, int lb, int rb, int tl, int tr) {
    if (tl <= lb && rb <= tr) {
        return t[v];
    }
    int ans = 0;
    int mid = lb + rb >> 1;
    if (tl < mid) ans += get(lt[v], lb, mid, tl, tr);
    if (mid < tr) ans += get(rt[v], mid, rb, tl, tr);
    return ans;
}

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, int> mp;
    vector<int> nxt(n);
    for (int i = n - 1; i >= 0; i--) {
        if (!mp.count(a[i])) {
            nxt[i] = n + 1;
        } else {
            nxt[i] = mp[a[i]];
        }
        mp[a[i]] = i;
    }
    memset(arr, 0, sizeof arr);
    vector<int> tr(n + 1);
    tr[0] = build(0, n + 2);
    for (int i = 1; i <= n; i++) {
        tr[i] = upd(tr[i - 1], 0, n + 2, nxt[i - 1]);
    }
    int p = 0, x, y;
    int q;
    cin >> q;
    while (q--) {
        cin >> x >> y;
        int lb = (x + p) % n + 1;
        int kk = (y + p) % m + 1;
        int ll = 0;
        int rr = n - lb;
        int lval = -1;
        while (rr - ll > 0) {
            int mid = (rr + ll) / 2;
            int lk = get(tr[lb - 1], 0, n + 2, lb + mid, n + 2);
            int rk = get(tr[lb + mid], 0, n + 2, lb + mid, n + 2);
            int val = rk - lk;
            if (val >= kk) {
                rr = mid;
                lval = 1;
            } else {
                ll = mid + 1;
            }
        }
        int lk = get(tr[lb - 1], 0, n + 2, lb + ll, n + 2);
        int rk = get(tr[lb + ll], 0, n + 2, lb + ll, n + 2);
        int val = rk - lk;
        if (val >= kk) {
            rr = ll;
            lval = 1;
        }
        if (lval == -1) {
            cout << 0 << '\n';
            p = 0;
        } else {
            cout << ll + lb << '\n';
            p = ll + lb;
        }
    }
}

signed main() {
#ifdef LOCA
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
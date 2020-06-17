//
// Created by watemus on 15.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#endif

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
#else
#endif

const int MAX = 1e7;
int cnt_v = 0;
const int MAX_N = 1e5 + 10;

int t[MAX], lt[MAX], rt[MAX];

inline int new_node() {
    lt[cnt_v] = -1;
    rt[cnt_v] = -1;
    return cnt_v++;
}

inline int cpy_node(int u) {
    int v = new_node();
    lt[v] = lt[u];
    rt[v] = rt[u];
    t[v] = t[u];
    return v;
}

int build(int lb, int rb) {
    int v = new_node();
    if (rb - lb == 1) {
        t[v] = 0;
    } else {
        int mid = (lb + rb) / 2;
        lt[v] = build(lb, mid);
        rt[v] = build(mid, rb);
    }
    return v;
}

int modify(int v, int lb, int rb, int at) {
    v = cpy_node(v);
    if (rb - lb == 1) {
        t[v]++;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid) {
            lt[v] = modify(lt[v], lb, mid, at);
        } else {
            rt[v] = modify(rt[v], mid, rb, at);
        }
        t[v] = t[lt[v]] + t[rt[v]];
    }
    return v;//
}

int get(int v, int lb, int rb, int ql, int qr) {
    if (ql <= lb && rb <= qr) {
        return t[v];
    }
    int ans = 0;
    int mid = (lb + rb) / 2;
    if (ql < mid) ans += get(lt[v], lb, mid, ql, qr);
    if (mid < qr) ans += get(rt[v], mid, rb, ql, qr);
    return ans;
}

void run() {
    int n, m;
    cin >> n >> m;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vec<int> nxt(n);
    map<int, int> mp;
    for (int i = n - 1; i >= 0; i--) {
        if (!mp.count(a[i])) {
            nxt[i] = n + 1;
        } else {
            nxt[i] = mp[a[i]];
        }
        mp[a[i]] = i + 1;
    }
    vec<int> st(n + 2);
    st[0] = build(0, n + 2);
    for (int i = 1; i <= n; i++) {
        st[i] = modify(st[i - 1], 0, n + 2, nxt[i - 1]);
    }
    int q;
    int p = 0;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        int ql = (x + p) % n + 1;
        int k = (y + p) % m + 1;
        int lb = ql;
        int rb = n + 1;
        while (lb < rb) {
            int mid = (lb + rb) / 2;
            int prev_val = get(st[ql - 1], 0, n + 2, mid + 1, n + 2);
            int curr_val = get(st[mid], 0, n + 2, mid + 1, n + 2);
            if (curr_val - prev_val >= k) {
                rb = mid;
            } else {
                lb = mid + 1;
            }
        }
        if (rb == n + 1) {
            cout << "0\n";
            rb = 0;
        } else {
            cout << rb << '\n';
        }
        p = rb;
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


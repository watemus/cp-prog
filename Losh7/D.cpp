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
#else
#endif

const int MAX = (1 << 22);

int t[MAX * 2 + 10], dt[MAX * 2 + 10];

void build(int v, int lb, int rb) {
    if (rb - lb == 1) {
        t[v] = 0;
        dt[v] = 0;
    } else {
        int mid = (lb + rb) / 2;
        build(v * 2 + 1, lb, mid);
        build(v * 2 + 2, mid, rb);
        t[v] = dt[v] = 0;
    }
}

inline void push(int v, int lb, int rb) {
    if (dt[v] == 1) {
        t[v] = 0;
        dt[v] = 0;
        if (rb - lb > 1) {
            dt[v * 2 + 1] = 1;
            dt[v * 2 + 2] = 1;
        }
    }
}

int get(int v, int lb, int rb, int ql, int qr) {
    push(v, lb, rb);
    if (ql <= lb && rb <= qr) {
        return t[v];
    } else {
        int ans = 0;
        int mid = (lb + rb) / 2;
        if (ql < mid) ans += get(v * 2 + 1, lb, mid, ql, qr);
        if (mid < qr) ans += get(v * 2 + 2, mid, rb, ql, qr);
        return ans;
    }
}

void add_one(int v, int lb, int rb, int at) {
    push(v, lb, rb);
    if (rb - lb == 1) {
        t[v] = 1;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid)
            add_one(v * 2 + 1, lb, mid, at);
        else
            add_one(v * 2 + 2, mid, rb, at);
        push(v * 2 + 1, lb, mid);
        push(v * 2 + 2, mid, rb);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }
}

void rem_ones(int v, int lb, int rb, int ql, int qr) {
    push(v, lb, rb);
    if (ql <= lb && rb <= qr) {
        dt[v] = 1;
        push(v, lb, rb);
    } else {
        int mid = (lb + rb) / 2;
        if (ql < mid) rem_ones(v * 2 + 1, lb, mid, ql, qr);
        if (mid < qr) rem_ones(v * 2 + 2, mid, rb, ql, qr);
        push(v * 2 + 1, lb, mid);
        push(v * 2 + 2, mid, rb);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }
}

void run() {
    int n, m;
    cin >> n >> m;
    //build(0, 0, MAX);
    vec<int> dep(n);
    vec<int> rp(n);
    for (int i = 0; i < n; i++) {
        cin >> dep[i];
        rp[i] =  i;
    }
    while (m--) {//
        int q;
        cin >> q;
        q--;
        if (q >= 0) {
            swap(dep[rp[q]], dep[rp[q + 1]]);
        } else {
            int ans = 0;
            vec<int> st;
            for (int i = 0; i < n; i++) {
                int ops = 0;
                while (st.size() && st.back() < dep[i]) {
                    ops++;
                    st.pop_back();
                }
                st.push_back(dep[i]);
                ans = max(ops, ans);
            }
            cout << ans << '\n';
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


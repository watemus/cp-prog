//
// Created by watemus on 09.06.2020.
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

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
const int MAXN = 100;
#else
const int MAXN = (1 << 17) + 10;
#endif


struct segtree1 {
    int t[MAXN * 2];

    void build(int v, int lb, int rb) {
        if (rb - lb == 1) {
            t[v] = 0;
        } else {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid);
            build(v * 2 + 2, mid, rb);
            t[v] = 0;
        }
    }

    void add(int v, int lb, int rb, int ql, int qr) {
        if (ql <= lb && rb <= qr) {
            t[v]++;
            return;
        }
        int mid = (lb + rb) / 2;
        if (ql < mid) {
            add(v * 2 + 1, lb, mid, ql, qr);
        }
        if (mid < qr) {
            add(v * 2 + 2, mid, rb, ql, qr);
        }
    }

    int get(int at, int n) {
        int v = 0;
        int lb = 0;
        int rb = n;
        int ans = t[0];
        while (lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            if (at < mid) {
                rb = mid;
                v = v * 2 + 1;
                ans += t[v];
            } else {
                lb = mid;
                v = v * 2 + 2;
                ans += t[v];
            }
        }
        return ans;
    }
};


struct segtree2 {
    tuple<int, int, int> t[MAXN * 2];
    int dt[MAXN * 2];
    int k;
    void build(int v, int lb, int rb, int kk) {
        k = kk;
        if (rb - lb == 1) {
            t[v] = {INFL, INFL, INFL};
        } else {
            int mid = (lb + rb) / 2;
            build(v * 2 + 1, lb, mid, k);
            build(v * 2 + 2, mid, rb, k);
            t[v] = {INFL, INFL, INFL};
            dt[v] = 0;
        }
    }
    void spush(int v, int lb, int rb) {
        int mid = (lb + rb) / 2;
        if (t[v] == make_tuple(INFL, INFL, INFL)) return;
        if (rb - lb == 1) {
            get<2>(t[v]) -= dt[v];
        } else {
            dt[v * 2 + 1] += dt[v];
            dt[v * 2 + 2] += dt[v];
            get<2>(t[v]) -= dt[v];
            dt[v] = 0;
        }
    }
    void rebuild(int v, int lb, int rb) {
        if (rb - lb == 1) return;

        if (t[v] == make_tuple(INFL, INFL, INFL)) return;
        int mid = (lb + rb) / 2;
        spush(v, lb, rb);
        rebuild(v * 2 + 1, lb, mid);
        rebuild(v * 2 + 2, mid, rb);
        t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
    }
    void push(int v, int lb, int rb) {
        int mid = (lb + rb) / 2;

        if (t[v] == make_tuple(INFL, INFL, INFL)) return;
        if (rb - lb == 1) {
            get<2>(t[v]) = ((get<2>(t[v]) - dt[v]) % k + k) % k;
        } else {
            dt[v * 2 + 1] += dt[v];
            dt[v * 2 + 2] += dt[v];
            if (dt[v] > get<2>(t[v])) {
                rebuild(v, lb, rb);
            } else {
                get<2>(t[v]) -= dt[v];
                dt[v] = 0;
            }
        }
    }
    tuple<int, int, int> merge(tuple<int, int, int> lhs,  tuple<int, int, int> rhs) {
        auto [val1, pos1, rem1] = lhs;
        auto [val2, pos2, rem2] = rhs;
        if (rem1 == rem2) {
            if (val1 == val2) {
                return pos1 < pos2 ? lhs : rhs;
            }
            return val1 > val2 ? lhs : rhs;
        }
        return rem1 < rem2 ? lhs : rhs;
    }
    void chg(int v, int lb, int rb, int at, tuple<int, int, int> val) {
        push(v, lb, rb);
        if (rb - lb == 1) {
            t[v] = val;
        } else {
            int mid = (lb + rb) / 2;
            push(v * 2 + 1, lb, mid);
            push(v * 2 + 2, mid, rb);
            if (at < mid)
                chg(v * 2 + 1, lb, mid, at, val);
            else
                chg(v * 2 + 2, mid, rb, at, val);
            t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }
    tuple<int, int, int> gett(int v, int lb, int rb, int ql, int qr) {
        push(v, lb, rb);
        if (ql <= lb && rb <= qr) {
            return t[v];
        } else {
            int mid = (lb + rb) / 2;
            tuple<int, int, int> ans = {INFL, INFL, INFL};
            if (ql < mid) {
                ans = merge(ans, gett(v * 2 + 1, lb, mid, ql, qr));
            }
            if (mid < qr) {
                ans = merge(ans, gett(v * 2 + 2, mid, rb, ql, qr));
            }
            return ans;
        }
    }
    void rmv(int v, int lb, int rb, int ql, int qr) {
        push(v, lb, rb);
        if (ql <= lb && rb <= qr) {
            dt[v]++;
            push(v, lb, rb);
        } else {
            int mid = (lb + rb) / 2;
            push(v * 2 + 1, lb, mid);
            push(v * 2 + 2, mid, rb);
            if (ql < mid) {
                rmv(v * 2 + 1, lb, mid, ql, qr);
            }
            if (mid < qr) {
                rmv(v * 2 + 2, mid, rb, ql, qr);
            }
        }
    }
};

void rmv(int lb, int rb, vec<int> &ans, segtree1 &t1, segtree2 &t2, int k) {
    while (true) {
        auto[val, pos, rem] = t2.gett(0, 0, rb, lb, rb);
        rem = (rem % k + k) % k;
        if (rem == 0 && pos != INFL) {
            ans.push_back(val);
            t1.add(0, 0, rb, pos, rb);
            t2.rmv(0, 0, rb, pos, rb);
            t2.chg(0, 0, rb, pos, {INFL, INFL, INFL});
            rmv(pos, rb, ans, t1, t2, k);
            continue;
        }
        break;
    }
}

void run() {
    int n, k;
    cin >> n >> k;
    vec<pair<int, int>> a(n);
    vec<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
        b[i] = a[i].first;
    }
    sort(all(a), [](auto a, auto b){
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first > b.first;
    });
    vec<int> usd(n);
    segtree1 t1;
    t1.build(0, 0, n);
    segtree2 t2;
    t2.build(0, 0, n, k);
    vec<int> ans;
    for (int i = 0; i < n; i++) {
        int pos = a[i].second;
        int mk = (pos - t1.get(a[i].second, n) + k) % k;
        if (mk == 0) {
            ans.push_back(a[i].first);
            t1.add(0, 0, n, pos, n);
            t2.rmv(0, 0, n, pos, n);
            rmv(pos, n, ans, t1, t2, k);
        } else {
            t2.chg(0, 0, n, pos, {a[i].first, pos, mk});
        }
    }
    for (auto el : ans) {
        cout << el << '\n';
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


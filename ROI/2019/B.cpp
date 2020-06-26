//
// Created by watemus on 23.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1 << 21;
int mn1[MAXN * 2 + 228], mx1[MAXN * 2 + 228];
int mn2[MAXN * 2 + 228], mx2[MAXN * 2 + 228];
struct segtree {
    int *mn, *mx;
    segtree(int *mn, int *mx) : mn(mn), mx(mx) {
        fill(mn, mn + MAXN, 0);
        fill(mx, mx + MAXN, 0);
    }
    void modify(int v, int lb, int rb, int at, int new_val) {
        if (rb - lb == 1) {
            mn[v] = mx[v] = new_val;
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid)
                modify(v * 2 + 1, lb, mid, at, new_val);
            else
                modify(v * 2 + 2, mid, rb, at, new_val);
            mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
            mn[v] = min(mn[v * 2 + 1], mn[v * 2 + 2]);
        }
    }
    int get_min(int v, int lb, int rb, int ql, int qr) {
        if (ql <= lb && rb <= qr)
            return mn[v];
        else {
            int ans = INFI;
            int mid = (lb + rb) / 2;
            if (ql < mid) {
                ans = min(ans, get_min(v * 2 + 1, lb, mid, ql, qr));
            }
            if (mid < qr) {
                ans = min(ans, get_min(v * 2 + 2, mid, rb, ql, qr));
            }
            return ans;
        }
    }
    int get_max(int v, int lb, int rb, int ql, int qr) {
        if (ql <= lb && rb <= qr)
            return mx[v];
        else {
            int ans = -INFI;
            int mid = (lb + rb) / 2;
            if (ql < mid) {
                ans = max(ans, get_max(v * 2 + 1, lb, mid, ql, qr));
            }
            if (mid < qr) {
                ans = max(ans, get_max(v * 2 + 2, mid, rb, ql, qr));
            }
            return ans;
        }
    }
    int descent_left(int v, int lb, int rb, int ql, int qr, int val) {
        if (rb <= ql || qr <= lb || mn[v] > val)
            return -1;
        if (rb - lb == 1) {
            return lb;
        }
        int mid = (lb + rb) / 2;
        int ans = descent_left(v * 2 + 2, mid, rb, ql, qr, val);
        if (ans == -1)
            return descent_left(v * 2 + 1, lb, mid, ql, qr, val);
        return ans;
    }
    int descent_right(int v, int lb, int rb, int ql, int qr, int val) {
        if (rb <= ql || qr <= lb || mn[v] > val) {
            return -1;
        }
        if (rb - lb == 1) {
            return lb;
        }
        int mid = (lb + rb) / 2;
        int ans = descent_right(v * 2 + 1, lb, mid, ql, qr, val);
        if (ans == -1)
            return descent_right(v * 2 + 2, mid, rb, ql, qr, val);
        return ans;
    }
};

void run() {
    int n, m, q;
    cin >> n >> m >> q;
    segtree t1(mn1, mx1), t2(mn2, mx2);
    vec<int> a1(n), a2(m);
    int step = 0;
    while (q--) {
        step++;
        int typ;
        cin >> typ;
        if (typ == 1) {
            int x;
            cin >> x;
            t1.modify(0, 0, n, x - 1, -step);
            a1[x - 1] = -step;
        } else if (typ == 2) {
            int x;
            cin >> x;
            t2.modify(0, 0, m, x - 1, -step);
            a2[x - 1] = -step;
        } else {
            int x1, y1, x2, y2, k;
            cin >> x1 >> y1 >> x2 >> y2 >> k;
            x1--, x2--, y1--, y2--;
            int mx = -step + k;
            int sh = abs(x2 - x1) + abs(y2 - y1);
            if (a1[x1] <= mx && a2[y2] <= mx) {
                cout << sh << '\n';
                continue;
            }
            if (a2[y1] <= mx && a1[x2] <= mx) {
                cout << sh << '\n';
                continue;
            }
            if (t1.get_max(0, 0, n, min(x1, x2), max(x1, x2) + 1) <= mx) {
                cout << sh << '\n';
                continue;
            }
            if (t2.get_max(0, 0, m, min(y1, y2), max(y1, y2) + 1) <= mx) {
                cout << sh << '\n';
                continue;
            }
            if (min(a1[x1], a2[y1]) > mx || min(a1[x2], a2[y2]) > mx) {
                cout << "-1\n";
                continue;
            }
            int ltx1 = t1.descent_left(0, 0, n, 0, x1 + 1, mx);
            int rtx1 = t1.descent_right(0, 0, n, x1, n, mx);
            int lty1 = t2.descent_left(0, 0, m, 0, y1 + 1, mx);
            int rty1 = t2.descent_right(0, 0, m, y1, m, mx);
            int ltx2 = t1.descent_left(0, 0, n, 0, x2 + 1, mx);
            int rtx2 = t1.descent_right(0, 0, n, x2, n, mx);
            int lty2 = t2.descent_left(0, 0, m, 0, y2 + 1, mx);
            int rty2 = t2.descent_right(0, 0, m, y2, m, mx);
            int ans = INFI;
            int dy = abs(y1 - y2);
            int dx = abs(x1 - x2);
            if (ltx1 != -1 && (a2[y1] <= mx) && (a2[y2] <= mx)) {
                ans = min(ans, dy + abs(x1 - ltx1) + abs(x2 - ltx1));
            }
            if (ltx2 != -1 && (a2[y1] <= mx) && (a2[y2] <= mx)) {
                ans = min(ans, dy + abs(x1 - ltx2) + abs(x2 - ltx2));
            }
            if (rtx1 != -1 && (a2[y1] <= mx) && (a2[y2] <= mx)) {
                ans = min(ans, dy + abs(x1 - rtx1) + abs(x2 - rtx1));
            }
            if (rtx2 != -1 && (a2[y1] <= mx) && (a2[y2] <= mx)) {
                ans = min(ans, dy + abs(x1 - rtx2) + abs(x2 - rtx2));
            }
            if (lty1 != -1 && (a1[x1] <= mx) && (a1[x2] <= mx)) {
                ans = min(ans, dx + abs(y1 - lty1) + abs(y2 - lty1));
            }
            if (lty2 != -1 && (a1[x1] <= mx) && (a1[x2] <= mx)) {
                ans = min(ans, dx + abs(y1 - lty2) + abs(y2 - lty2));
            }
            if (rty1 != -1 && (a1[x1] <= mx) && (a1[x2] <= mx)) {
                ans = min(ans, dx + abs(y1 - rty1) + abs(y2 - rty1));
            }
            if (rty2 != -1 && (a1[x1] <= mx) && (a1[x2] <= mx)) {
                ans = min(ans, dx + abs(y1 - rty2) + abs(y2 - rty2));
            }
            cout << (ans == INFI ? -1 : ans) << '\n';
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


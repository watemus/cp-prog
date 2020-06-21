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

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAX_N = 20;
const int MAX_M = (1 << 16);

int t[MAX_N][MAX_M * 2 + 228];
int vals[MAX_N][MAX_M];

void build(int i, int v, int lb, int rb) {
    if (rb - lb == 1) {
        t[i][v] = 1;
    } else {
        int mid = (lb + rb) / 2;
        build(i, v * 2 + 1, lb, mid);
        build(i, v * 2 + 2, mid, rb);
        t[i][v] = t[i][v * 2 + 1] + t[i][v * 2 + 2];
    }
}

int get_left(int i, int v, int lb, int rb, int ql, int qr) {
    if (rb <= ql || lb >= qr || t[i][v] == 0)
        return -1;
    if (rb - lb == 1) {
        return lb;
    }
    int mid = (lb + rb) / 2;
    int ans = get_left(i, v * 2 + 1, lb, mid, ql, qr);
    if (ans == -1)
        ans = get_left(i, v * 2 + 2, mid, rb, ql, qr);
    return ans;
}

int get_right(int i, int v, int lb, int rb, int ql, int qr) {
    if (rb <= ql || lb >= qr || t[i][v] == 0)
        return -1;
    if (rb - lb == 1) {
        return lb;
    }
    int mid = (lb + rb) / 2;
    int ans = get_right(i, v * 2 + 2, mid, rb, ql, qr);
    if (ans == -1)
        ans = get_right(i, v * 2 + 1, lb, mid, ql, qr);
    return ans;
}

void modify(int i, int v, int lb, int rb, int at) {
    if (rb - lb == 1) {
        t[i][v] = 0;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid) {
            modify(i, v * 2 + 1, lb, mid, at);
        } else {
            modify(i, v * 2 + 2, mid, rb, at);
        }
        t[i][v] = t[i][v * 2 + 1] + t[i][v * 2 + 2];
    }
}

void run() {
    int n = 0, m = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        build(i, 0, 0, m);
        memset(vals[i], 0, sizeof vals[i]);
    }
    int k;
    cin >> k;
    while (k--) {
        string q;
        cin >> q;
        if (q == "Color") {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            modify(x, 0, 0, m, y);
            vals[x][y] = 1;
        } else {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            int lst = get_left(x, 0, 0, m, y + 1, m);
            int rst = get_right(x, 0, 0, m, 0, y);
            int ust = -1, dst = -1;
            for (int i = x - 1; i >= 0; i--) {
                if (vals[i][y] == 0) {
                    ust = i;
                    break;
                }
            }
            for (int i = x + 1; i < n; i++) {
                if (vals[i][y] == 0) {
                    dst = i;
                    break;
                }
            }
            int ans = INFL;
            vector<pair<int, int>> vans;
            if (lst != -1 && abs(lst - y) < ans) {
                ans = abs(lst - y);
                //vans.clear();
                vans.emplace_back(x, lst);
            }
            else if (lst != -1) vans.emplace_back(x, lst);
            if (rst != -1 && abs(rst - y) < ans) {
                ans = abs(rst - y);
                //vans.clear();
                vans.emplace_back(x, rst);
            }
            else if (rst != -1) vans.emplace_back(x, rst);
            if (ust != -1 && abs(ust - x) < ans) {
                ans = abs(ust - x);
                //vans.clear();
                vans.emplace_back(ust, y);
            }
            else if (ust != -1) vans.emplace_back(ust, y);
            if (dst != -1 && abs(dst - x) < ans) {
                ans = abs(dst - x);
                //vans.clear();//
                vans.emplace_back(dst, y);
            }
            else if (dst != -1) vans.emplace_back(dst, y);
            cout << vans.size() << '\n';
            for (auto pr : vans) {
                cout << pr.first + 1 << ' ' << pr.second + 1 << '\n';
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


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
#else
#endif

const int MAXN = (1 << 18) + 228;

int t[MAXN];
int a[MAXN];

void build(int v, int lb, int rb) {
    if (rb - lb == 1) {
        t[v] = 1;
    } else {
        int mid = (lb + rb) / 2;
        build(v * 2 + 1, lb, mid);
        build(v * 2 + 2, mid, rb);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2] - (a[mid - 1] == a[mid]);
    }
}

void upd(int v, int lb, int rb, int at, int nw) {
    if (rb - lb == 1) {
        a[lb] = nw;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid)
            upd(v * 2 + 1, lb, mid, at, nw);
        else
            upd(v * 2 + 2, mid, rb, at, nw);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2] - (a[mid - 1] == a[mid]);
    }
}

void run() {
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n);
    cin >> q;
    while (q--) {
        int p, x;
        cin >> p >> x;
        p--;
        upd(0, 0, n, p, x);
        cout << t[0] << '\n';
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


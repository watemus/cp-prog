//
// Created by watemus on 16.06.2020.
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

const int LOGN = 19;

void run() {
    int n, m;
    cin >> n >> m;
    vec<int> tm(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> tm[i];
    }
    vec<vec<int>> a(n, vec<int>(m)), can(n, vec<int>(m)), up(n, vec<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i][j] + tm[i] <= a[i + 1][j - 1]) {
                can[i][j] = 1;
            }
        }
    }
    vec<vec<vec<int>>> bup(n, vec<vec<int>>(m, vec<int>(LOGN)));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < LOGN; j++) {
            bup[n - 1][i][j] = i;
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (j < m - 1 && can[i][j + 1]) {
                up[i][j] = up[i][j + 1] + 1;
            }
            bup[i][j][0] = j + up[i][j];
            for (int k = 1; k < LOGN; k++) {
                bup[i][j][k] = bup[min(i + (1 << (k - 1)), n - 1)][bup[i][j][k - 1]][k - 1];
            }
        }
    }
    int q;
    cin >> q >> q;

    while (q--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        w--;
        for (int i = LOGN - 1; i >= 0; i--) {
            if (u + (1 << i) <= v) {
                w = bup[u][w][i];
                u += (1 << i);
            }
        }
        cout << a[v][w] << '\n';
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


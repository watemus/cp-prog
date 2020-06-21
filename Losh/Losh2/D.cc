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

void run() {
    int p;
    cin >> p;
    int n, m;
    cin >> n >> m;
    vec<vec<int>> hor(n, vec<int>(m)), ver(n, vec<int>(m));
    vec<vec<int>> f(n, vec<int>(m));
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int tp, x, y, cnt;
        cin >> tp >> x >> y >> cnt;
        x--; y--;
        if (tp == 0) {
            hor[x][y] = max(hor[x][y], cnt);
        } else {
            ver[x][y] = max(ver[x][y], cnt);
        }
    }
    vec<int> c_hor(n), c_ver(m);
    int ans1 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c_hor[i] = max(c_hor[i], hor[i][j]);
            c_ver[j] = max(c_ver[j], ver[i][j]);
            if (c_hor[i] || c_ver[j]) {
                f[i][j] = 1;
            } else {
                ans1++;
            }
            c_hor[i] = max(0LL, c_hor[i] - 1);
            c_ver[j] = max(0LL, c_ver[j] - 1);
        }
    }
    if (p == 1) {
        cout << ans1 << '\n';
        return;
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


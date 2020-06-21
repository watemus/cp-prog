//
// Created by watemus on 19.06.2020.
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

void run() {
    int n;
    cin >> n;
    vec<vec<int>> c2(n, vec<int>(n)), c5(n, vec<int>(n)), z(n, vec<int>(n));
    vec<vec<char>> prz(n, vec<char>(n));
    vec<vec<char>> pr2(n, vec<char>(n)), pr5(n, vec<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int el;
            cin >> el;
            if (el == 0) {
                z[i][j] = 1;
                c2[i][j] = c5[i][j] = 1;
            } else {
                while (el % 2 == 0) {
                    c2[i][j]++;
                    el /= 2;
                }
                while (el % 5 == 0) {
                    c5[i][j]++;
                    el /= 5;
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        c2[i][0] += c2[i - 1][0];
        c5[i][0] += c5[i - 1][0];
        pr2[i][0] = 'D';
        pr5[i][0] = 'D';
        c2[0][i] += c2[0][i - 1];
        c5[0][i] += c5[0][i - 1];
        pr2[0][i] = 'R';
        pr5[0][i] = 'R';
        prz[0][i] = 'R';
        prz[i][0] = 'D';
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            {
                int a1 = c2[i][j] + c2[i - 1][j];
                int a2 = c2[i][j] + c2[i][j - 1];
                if (a1 < a2) {
                    c2[i][j] = c2[i][j] + c2[i - 1][j];
                    pr2[i][j] = 'D';
                } else {
                    c2[i][j] = c2[i][j] + c2[i][j - 1];
                    pr2[i][j] = 'R';
                }
            }
            {
                int a1 = c5[i][j] + c5[i - 1][j];
                int a5 = c5[i][j] + c5[i][j - 1];
                if (a1 < a5) {
                    c5[i][j] = c5[i][j] + c5[i - 1][j];
                    pr5[i][j] = 'D';
                } else {
                    c5[i][j] = c5[i][j] + c5[i][j - 1];
                    pr5[i][j] = 'R';
                }
            }
            {
                int a1 = z[i][j] + z[i - 1][j];
                int a5 = z[i][j] + z[i][j - 1];
                if (a1 > a5) {
                    z[i][j] = z[i][j] + z[i - 1][j];
                    prz[i][j] = 'D';
                } else {
                    z[i][j] = z[i][j] + z[i][j - 1];
                    prz[i][j] = 'R';
                }
            }
        }
    }
    int ans = min(c2[n - 1][n - 1], c5[n - 1][n - 1]);
    bool zz = false;
    if (ans != 0 && z[n-1][n-1] > 0) {
        cout << 1 << '\n';
        zz = true;
    } else {
        cout << ans << '\n';
    }
    string way;
    int i = n - 1;
    int j = n - 1;
    auto &pr = pr2;
    if (c5[n - 1][n - 1] == ans) {
        pr = pr5;
    }
    if (zz) {
        pr = prz;
    }
    while (i != 0 || j != 0) {
        way.push_back(pr[i][j]);
        if (pr[i][j] == 'D') i--;
        else j--;
    }
    reverse(all(way));
    cout << way << '\n';
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


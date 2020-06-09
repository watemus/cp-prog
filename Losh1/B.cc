//
// Created by watemus on 08.06.2020.
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

const int MAXN = 700;
const int MAXM = 500;

int dp[MAXM][MAXN];
int sdp[MAXN][MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    //n = 700;
    //m = 500;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
       cin >> a[i];
       // a[i] = 1000;
    }
    for (int i = 0; i < m; i++) {
        {
            fill(dp[i], dp[i] + n, INFL);
        }
    }
    for (int i = 0; i < n; i++) {
        sdp[i][i] = a[i];

    }
    dp[0][0] = a[0];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sdp[i][j] = sdp[i][j - 1] + (j - i + 1) * a[j];
            if (i == 0) dp[0][j] = sdp[i][j];
        }
    }
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                dp[i][k] = min(dp[i][k], dp[i - 1][j] + sdp[j + 1][k]);
            }
        }
    }
    cout << dp[m-1][n-1] << '\n';
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


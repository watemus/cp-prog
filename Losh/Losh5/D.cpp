//
// Created by watemus on 12.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif


const int MAXN = 1e5 + 10;
const int MAXA = 26;
int pi[MAXN][MAXA];

void run() {
    int n, a, k;
    cin >> n >> a >> k;
    string s;
    cin >> s;
    for (int i = 0; i < a; i++) {
        pi[0][i] = 0;
    }
    auto t = s;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < a; j++) {
            s[i] = 'a' + j;
            int cr = pi[i - 1][s[i - 1] - 'a'];
            while (j != s[cr] - 'a' && cr > 0) {
                cr = pi[cr - 1][s[cr - 1] - 'a'];
            }
            if (j == s[cr] - 'a') {
                pi[i][j] = cr + 1;
            }
        }
        s[i] = t[i];
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a; j++) {
            if (j == s[i] - 'a') continue;
            ans = max(ans, (i - pi[i][j]) * (k + 1) + pi[i][j] + (n - i));
        }
    }
    cout << ans << '\n';
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


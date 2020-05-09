//
// Created by watemus on 01.05.2020.
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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif


void run() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].ff >> a[i].ss;
    vector<vector<int>> r(n + 1, vector<int>(k + 1));
    vector<vector<int>> b(n + 1, vector<int>(k + 1));
    vector<vector<int>> c(n + 1, vector<int>(k + 1));
    vector<int> r1(n + 1);
    vector<int> b1(n + 1);
    vector<int> c1(n + 1);
    for (int i = 1; i <= n; i++) {
        int cr = r1[i - 1] + a[i - 1].ff;
        int cb = b1[i - 1] + a[i - 1].ss;
        if (c1[i] < c1[i - 1] + cr / k + cb / k) {
            c1[i] = c1[i - 1] + cr / k + cb / k;
            r1[i] = cr % k;
            b1[i] = cr % k;
        }
        for (int kk = 0; kk <= k; kk++) {
            int cr = r[i - 1][kk] + a[i - 1].ff;
            int cb = b[i - 1][kk] + a[i - 1].ss;
            if (c1[i] < c[i - 1][kk] + cr / k + cb / k) {
                c1[i] = c[i - 1][kk] + cr / k + cb / k;
                r1[i] = cr % k;
                b1[i] = cb % k;
            }
        }
        if (a[i - 1].ff + a[i - 1].ss < k) continue;
        for (int kk = 0; kk <= min(a[i - 1].ff; kk++) {

        }
    }
    cout << max(c1[n], c[n]) << endl;
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
//
// Created by watemus on 27.03.2020.
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

const int MAXN = 2008;
const int MAXK = 13;
const int MOD = 1e9 + 7;

signed dp[MAXN][1 << MAXK][2];
bool was[MAXN][1 << MAXK][2];

void run() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[0][0][0] = 1;
    was[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int msk = 0; msk < (1 << k); msk++) {
            dp[i][msk][0] = dp[i][msk][1] = 0;
        }
        for (int msk = 0; msk < (1 << k - 1); msk++) {
            if (was[i - 1][msk][0]) {
                if (a[i] == 2 || a[i] == 0) {
                    int nw = (msk + 1) & ((1 << k - 1) - 1);
                    dp[i][nw][nw == 0] += dp[i - 1][msk][0];
                    dp[i][nw][nw == 0] %= MOD;
                    was[i][nw][nw == 0] = 1;
                }
                if (a[i] == 4 || a[i] == 0) {
                    if (msk & 1) {
                        dp[i][2][0] += dp[i - 1][msk][0];
                        dp[i][2][0] %= MOD;
                        was[i][2][0] = 1;
                    } else {
                        int nw = (msk + 2) & ((1 << k - 1) - 1);
                        dp[i][nw][nw == 0] += dp[i - 1][msk][0];
                        dp[i][nw][nw == 0] %= MOD;
                        was[i][nw][nw == 0] = 1;
                    }
                }
            }
            if (was[i - 1][msk][1]) {
                if (a[i] == 2 || a[i] == 0) {
                    dp[i][(msk + 1) & ((1 << k - 1) - 1)][1] += dp[i - 1][msk][1];
                    dp[i][(msk + 1) & ((1 << k - 1) - 1)][1] %= MOD;
                    was[i][(msk + 1) & ((1 << k - 1) - 1)][1] = 1;
                }
                if (a[i] == 4 || a[i] == 0) {
                    if (msk & 1) {
                        dp[i][2][1] += dp[i - 1][msk][1];
                        dp[i][2][1] %= MOD;
                        was[i][2][1] = 1;
                    } else {
                        dp[i][(msk + 2) & ((1 << k - 1) - 1)][1] += dp[i - 1][msk][1];
                        dp[i][(msk + 2) & ((1 << k - 1) - 1)][1] %= MOD;
                        was[i][(msk + 2) & ((1 << k - 1) - 1)][1] = 1;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int msk = 0; msk < (1 << k); msk++) {
        ans += dp[n][msk][1];
        ans %= MOD;
    }
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
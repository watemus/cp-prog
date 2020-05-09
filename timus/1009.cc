//
// Created by watemus on 16.04.2020.
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
    vector<vector<int>> dp(n, vector<int>(k));
    for (int i = 1; i < k; i++) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < k; j++) {
            for (int h = 0; h < k; h++) {
                if (j == 0 && h == 0) continue;
                dp[i][h] += dp[i - 1][j];
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans += dp[n - 1][i];
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
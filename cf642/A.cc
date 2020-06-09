//
// Created by watemus on 14.05.2020.
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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif


void run() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    vector<int> interest;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            interest.push_back(a[i][j] - i - j);
        }
    }
    int ans = INT64_MAX;
    for (auto st : interest) {
        if (st > a[0][0]) continue;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        dp[0][0] = a[0][0] - st;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) continue;
                if (a[i][j] < st + i + j) continue;
                dp[i][j] = INT64_MAX;
                if (i > 0 && dp[i - 1][j] != -1) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i][j] - st - i - j);
                }
                if (j > 0 && dp[i][j - 1] != -1) {
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + a[i][j] - st - i - j);
                }
                if (dp[i][j] == INT64_MAX) {
                    dp[i][j] = -1;
                }
            }
        }
        if (dp[n - 1][m - 1] == -1) continue;
        ans = min(ans, dp[n - 1][m - 1]);
    }
    cout << ans << '\n';
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
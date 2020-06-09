//
// Created by watemus on 20.05.2020.
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

constexpr int MAX_N = 3e5 + 10;
constexpr int MAX_M = 4;
constexpr int MAX_STATES = 3;

int dp[MAX_N][MAX_STATES][MAX_STATES][MAX_STATES][MAX_STATES];

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> lb(m), rb(m);
    for (int i = 0; i < m; i++) {
        cin >> lb[i] >> rb[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int state1 = 0; state1 < MAX_STATES; state1++) {
            for (int state2 = 0; state2 < MAX_STATES; state2++) {
                for (int state3 = 0; state3 < MAX_STATES; state3++) {
                    for (int state4 = 0; state4 < MAX_STATES; state4++) {
                        dp[i][state1][state2][state3][state4] = (INFL);
                    }
                }
            }
        }
    }
    dp[0][0][0][0][0] = 0;
    int ans = INFL;
    for (int i = 1; i <= n; i++) {
        for (int s1 = 0; s1 < MAX_STATES; s1++) {
            if (s1 > 0 && lb[0] > i) continue;
            if (s1 == 1 && rb[0] < i) continue;
            for (int s2 = 0; s2 < MAX_STATES; s2++) {
                if (m <= 1 && s2 > 0) continue;
                if (s2 > 0 && lb[1] > i) continue;
                if (s2 == 1 && rb[1] < i) continue;
                for (int s3 = 0; s3 < MAX_STATES; s3++) {
                    if (m <= 2 && s3 > 0) continue;
                    if (s3 > 0 && lb[2] > i) continue;
                    if (s3 == 1 && rb[2] < i) continue;
                    for (int s4 = 0; s4 < MAX_STATES; s4++) {
                        if (m <= 3 && s4 > 0) continue;
                        if (s4 > 0 && lb[3] > i) continue;
                        if (s4 == 1 && rb[3] < i) continue;
                        int dt = a[i] * m;
                        if (s4 == 1) dt = (a[i] * 3);
                        if (s3 == 1) dt = (a[i] * 2);
                        if (s2 == 1) dt = (a[i] * 1);
                        if (s1 == 1) dt = (a[i] * 0);
                        for (int ds1 : {0, 1}) {
                            if (ds1 > s1) continue;
                            for (int ds2 : {0, 1}) {
                                if (ds2 > s2) continue;
                                for (int ds3 : {0, 1}) {
                                    if (ds3 > s3) continue;
                                    for (int ds4 : {0, 1}) {
                                        if (ds4 > s4) continue;
                                        dp[i][s1][s2][s3][s4] = min(dp[i][s1][s2][s3][s4], dp[i - 1][s1-ds1][s2-ds2][s3-ds3][s4-ds4] + dt);
                                        if (i == n) {
                                            ans = min(ans, dp[i][s1][s2][s3][s4]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
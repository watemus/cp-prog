//
// Created by watemus on 30.03.2020.
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

int n, m;

const int MOD = 1e9 + 7;

bool check(int pmsk, int msk) {
    for (int i = 0; i < m - 1; i++) {
        int f1 = bool(pmsk & (1LL << i));
        int s1 = bool(pmsk & (1LL << i + 1));
        int f2 = bool(msk & (1LL << i));
        int s2 = bool(msk & (1LL << i + 1));
        if (f1 == f2 && s1 == s2 && s1 == f1) {
            return false;
        }
    }
    return true;
}

void run() {
    cin >> n >> m;
    if (m > n) swap(n, m);
    vector<vector<int>> dp(n, vector<int>(1 << m));
    for (int msk = 0; msk < (1 << m); msk++) {
        dp[0][msk] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int msk = 0; msk < (1 << m); msk++) {
            for (int pmsk = 0; pmsk < (1 << m); pmsk++) {
                if (check(msk, pmsk)) {
                    dp[i][msk] += dp[i - 1][pmsk];
                }
            }
        }
    }
    int ans = 0;
    for (int msk = 0; msk < (1 << m); msk++) {
        ans += dp[n - 1][msk];
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
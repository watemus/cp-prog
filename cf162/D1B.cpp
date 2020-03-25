//
// Created by watemus on 26.03.2020.
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

const int MAXN = 1e5 + 10;

void run() {
    int n;
    cin >> n;
    vector<int> dp(MAXN, 0), a(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vector<int> divs {a[i]};
        int longest = 0;
        for (int div = 2; div * div <= a[i]; div++) {
            if (a[i] % div) {
                continue;
            }
            divs.push_back(div);
            divs.push_back(a[i] / div);
            longest = max({longest, dp[div], dp[a[i] / div]});
        }
        ans = max(ans, longest + 1);
        for (int div : divs) {
            dp[div] = max(dp[div], longest + 1);
        }
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
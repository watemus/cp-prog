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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &el : a) cin >> el;
    int ans = LONG_LONG_MAX;
    for (int msk = 0; msk < (1 << n); msk++) {
        int cr = 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1LL << i)) {
                cr += a[i];
            } else {
                cr -= a[i];
            }
        }
        ans = min(ans, abs(cr));
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
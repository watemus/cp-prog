//
// Created by watemus on 09.05.2020.
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
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].ff;
        a[i].ss = i;
    }
    int ans = 0;
    for (int i = 0; i < n * 3; i++) {
        for (int j = 0; j < n - 1; j++) {
            int cval = a[j].ff * abs(a[j].ss - j) + a[j + 1].ff * abs(a[j+1].ss - (j + 1));
            int nval = a[j].ff * abs(a[j].ss - (j + 1)) + a[j + 1].ff * abs(a[j+1].ss - j);
            if (nval >= cval) {
                swap(a[j], a[j + 1]);
                ans += nval - cval;
            }
        }
    }
    cout << ans << endl;
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
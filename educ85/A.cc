//
// Created by watemus on 10.04.2020.
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
    for (auto &[x, y] : a) cin >> x >> y;
    for (auto &[x, y] : a) {
        if (x < y) {
            puts("NO");
            return;
        }
    }
    for (int i = 1; i < n; i++) {
        if (a[i].first < a[i - 1].ff || a[i].ss < a[i - 1].ss ||
            a[i].ff - a[i - 1].ff < a[i].ss - a[i - 1].ss) {
            puts("NO");
            return;
        }
    }
    puts("YES");
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
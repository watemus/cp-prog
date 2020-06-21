//
// Created by watemus on 26.04.2020.
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
const int BS = 2;
#else
const int BS = 500;
#endif

void run() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    while (k--) {
        char q;
        cin >> q;
        if (q == 'A') {
            int at, x;
            cin >> at >> x;
            at--;
            b[at / BS] -= a[at];
            a[at] = x;
            b[at / BS] += x;
        } else {
            int l, r;
            cin >> l >> r;
            int ans = 0;
            l--;
            r--;
            while (l % BS && l <= r) {
                ans += a[l];
                l++;
            }
            while (l + BS < r) {
                ans += b[l / BS];
                l += BS;
            }
            while (l <= r) {
                ans += a[l];
                l++;
            }
            cout << ans << '\n';
        }
    }
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
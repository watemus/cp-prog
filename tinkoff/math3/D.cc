//
// Created by watemus on 14.04.2020.
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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif

const int MAXN = 1e7 + 10;

int phi[MAXN], d[MAXN];

void run() {
    phi[1] = d[1] = 1;
    for (int i = 2; i * i <= MAXN; i++) {
        if (d[i] != 0) continue;
        d[i] = i;
        for (int j = i * i; j < MAXN; j += i) {
            if (d[j] == 0) d[j] = i;
        }
    }
    for (int i = 2; i < MAXN; i++) {
        if (d[i] == 0) {
            d[i] = i;
        }
        if (d[i/d[i]] == d[i]) {
            phi[i] = phi[i/d[i]] * d[i];
        } else {
            phi[i] = phi[i/d[i]] * (d[i] - 1);
        }
    }
    ll ans = 0;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        ans += phi[i];
        //cout << phi[i] << ' ';
    }
    cout << ans * 2 - 1 << '\n';
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
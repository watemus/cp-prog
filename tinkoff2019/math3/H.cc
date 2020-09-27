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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif


void run() {
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        cout << n << "\n";
        return;
    }
    vector<int> divs;
    int tm = m;
    for (int i = 2; i*i <= m; i++) {
        while (tm % i == 0) {
            tm/=i;
            divs.push_back(i);
        }
    }
    if (tm>1){
        divs.push_back(tm);
    }
    divs.resize(unique(all(divs))-divs.begin());
    int mt = 1;
    int ans = n;
    for (int d : divs) {
        mt *= d;
        if (d > n) break;
        ans -= (n - d + 1) / mt + 1;
        cout << ans;
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
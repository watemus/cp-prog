//
// Created by watemus on 01.04.2020.
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

void run() {
    int n;
    cin >> n;
    vector<int> perm = {0, 5, 3, 1, 4, 2};
    int ans = 0;
    int st = 5;
    for (auto el : perm) {
        int cr = bool(n & (1 << (5 - el)));
        ans += cr * (1 << st);
        st--;
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
//
// Created by watemus on 03.05.2020.
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

int calc(int alen, int mlen) {
    int ans = alen * (mlen);
    ans -= (mlen * (mlen - 1) / 2);
    return ans;
}

void run() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int alen = b - a + 1;
    int mlen = b - a + 1;
    int ans = 0;
    while (c > a && mlen > 0) {
        if (c <= b) {
            alen--;
        }
        ans += calc(alen, mlen);
        mlen--;
        c--;
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
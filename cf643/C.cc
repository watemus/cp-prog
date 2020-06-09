//
// Created by watemus on 16.05.2020.
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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif


void run() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int ans = 0;
    int cnt = 0;
    for (int i = a; i <= b; i++) {
        int fst = i;
        int scd = c - fst + 1;
        cnt += c - max(b, scd) + 1;
    }
    for (int i = c; i <= d; i++) {
        ans += cnt;
        int mnfst = max((i + 1) - c, a);
        int mxfst = min((i + 1) - b, b);
        cnt -= max(0LL, mxfst - mnfst + 1);
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
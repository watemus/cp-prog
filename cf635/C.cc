//
// Created by watemus on 15.04.2020.
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

const int MAXN = 3e5;

void run() {
    vector<int> cnt(3);
    cin >> cnt[0] >> cnt[1] >> cnt[2];
    vector<int> p = {0, 1, 2};
    vector<vector<int>> a {vector<int>(cnt[0]), vector<int>(cnt[1]), vector<int>(cnt[2])};
    for (int i : {0, 1, 2}) {
        for (auto &el : a[i]) cin >> el;
        sort(all(a[i]));
    }
    int ans = LONG_LONG_MAX;
    do {
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < cnt[p[0]]) {
            while (j < 0) j++;
            while (j < cnt[p[1]] && a[p[1]][j] < a[p[0]][i]) j++;
            if (j == cnt[p[1]]) break;
            while (k < 0) k++;
            while (k < cnt[p[2]] && (a[p[1]][j] + a[p[0]][i]) / 2 > a[p[2]][k]) {
                int x = (a[p[0]][i]);
                int y = (a[p[1]][j]);
                int z = (a[p[2]][k]);
                ans = min(ans, (x - y) * (x - y) + (x - z) * (x - z) + (y - z) * (y - z));
                k++;
            }
            if (k == cnt[p[2]]) break;
            else {

                int x = (a[p[0]][i]);
                int y = (a[p[1]][j]);
                int z = (a[p[2]][k]);
                ans = min(ans, (x - y) * (x - y) + (x - z) * (x - z) + (y - z) * (y - z));
            }
            if (k < cnt[p[2]] - 1) {
                int x = (a[p[0]][i]);
                int y = (a[p[1]][j]);
                int z = (a[p[2]][k + 1]);
                ans = min(ans, (x - y) * (x - y) + (x - z) * (x - z) + (y - z) * (y - z));
            }
            k-=30;
            j -= 30;
            i++;
        }
    } while (next_permutation(all(p)));
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
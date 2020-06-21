//
// Created by watemus on 05.05.2020.
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

const int MAX = 12;

int ind[1 << MAX];

void run() {
    int n, m;
    cin >> n >> m;
    bool has_0 = false;
    if (m == 0) {
        puts("NO");
        return;
    }
    for (int i = 0; i < m; i++) {
        int d;
        cin >> d;
        if (d == 0) has_0 = true;
        int cur_mask = 0;
        for (int i = 0; i < d; i++) {
            int elem;
            cin >> elem;
            cur_mask += (1 << (elem - 1));
        }
        ind[cur_mask] = 1;
    }
    if (!has_0) {
        puts("NO");
        return;
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!ind[mask]) continue;
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) && (!ind[mask ^ (1 << i)])) {
                puts("NO");
                return;
            }
        }
    }
    for (int mask1 = 0; mask1 < (1 << n); mask1++) {
        if (!ind[mask1]) continue;
        for (int mask2 = 0; mask2 < (1 << n); mask2++) {
            if (!ind[mask2]) continue;
            if (__builtin_popcount(mask2) >= __builtin_popcount(mask1)) continue;
            bool checked = false;
            for (int i = 0; i < n; i++) {
                if ((mask1 & (1 << i)) && !(mask2 & (1 << i)) && (ind[mask2 ^ (1 << i)])) {
                    checked = true;
                    break;
                }
            }
            if (!checked) {
                puts("NO");
                return;
            }
        }
    }
    puts("YES");
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
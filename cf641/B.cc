//
// Created by watemus on 12.05.2020.
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt += a[i] == k;
    }
    if (cnt == n) {
        puts("yes");
        return;
    }
    if (cnt == 0) {
        puts("no");
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        if (a[i] >= k && a[i + 1] >= k) {
            puts("yes");
            return;
        }
        if (a[i] >= k && a[i + 2] >= k) {
            puts("yes");
            return;
        }
    }
    puts("no");
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
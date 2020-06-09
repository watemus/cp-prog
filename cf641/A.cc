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
    map<int, int> m1, m2, cnt;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int ta = a[i];
        for (int d = 2; d * d <= ta; d++) {
            if (ta % d == 0) {
                cnt[d]++;
                int tcnt = 0;
                while (ta % d == 0) {
                    tcnt++;
                    ta /= d;
                }
                if (!m1[d]) {
                    m1[d] = INFL;
                    m2[d] = INFL;
                }
                int mm1 = m1[d];
                int mm2 = m2[d];
                if (tcnt <= mm1) {
                    m2[d] = m1[d];
                    m1[d] = tcnt;
                } else if (tcnt <= mm2) {
                    m2[d] = tcnt;
                }
            }
        }
        int d = ta;
        if (d > 1) {
            {
                cnt[d]++;
                if (!m1[d]) {
                    m1[d] = INFL;
                    m2[d] = INFL;
                }
                int mm1 = m1[d];
                int mm2 = m2[d];
                if (1 <= mm1) {
                    m2[d] = m1[d];
                    m1[d] = 1;
                } else if (1 <= mm2) {
                    m2[d] = 1;
                }
            }
        }
    }
    int ans = 1;
    for (auto [x, y] : cnt) {
        if (y == n - 1) {
            for (int i = 0; i < m1[x]; i++) {
                ans *= x;
            }
        } else if (y == n) {
            for (int i = 0; i < m2[x]; i++) {
                ans *= x;
            }
        }
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
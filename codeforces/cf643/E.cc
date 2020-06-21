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
    int n, a, r, m;
    cin >> n >> a >> r >> m;
    vector<int> c(n), suf(n), pref(n);
    int sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        sm += c[i];
    }
    sort(all(c));
    suf[n - 1] = c[n - 1];
    pref[0] = c[0];
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + c[i];
    }
    for (int i = n - 2; i >= 0; i--) {
        suf[i] = suf[i + 1] + c[i];
    }
    int ans = INT64_MAX;
    for (int i = 0; i < n; i++) {
        int need_lt = i * c[i];
        int need_rt = (n - i - 1) * c[i];
        int dst = need_lt - (i > 0 ? pref[i - 1] : 0);
        int src = (i < n - 1 ? suf[i + 1] : 0) - need_rt;
        int mn_cnt = min(dst, src);
        int cans = mn_cnt * min(m, a + r);
        cans += a * (dst - mn_cnt);
        cans += r * (src - mn_cnt);
        ans = min(cans, ans);
    }
    if (sm % n == 0) {
        int cans = 0;
        for (int i = 0; i < n; i++) {
            cans += max(c[i] - sm / n, 0LL) * min(a + r, m);
        }
        ans = min(ans, cans);
    }
    {
        int cans = 0;
        int to = sm / n;
        int dst = 0, src = 0;
        for (int i = 0; i < n; i++) {
            dst += max(0LL, to - c[i]);
            src += max(0LL, c[i] - to);
        }
        int mn = min(src, dst);
        cans += mn * min(a + r, m);
        src -= mn;
        dst -= mn;
        cans += src * r;
        cans += dst * a;
        ans = min(cans, ans);
    }
    {
        int cans = 0;
        int to = sm / n + 1;
        int dst = 0, src = 0;
        for (int i = 0; i < n; i++) {
            dst += max(0LL, to - c[i]);
            src += max(0LL, c[i] - to);
        }
        int mn = min(src, dst);
        cans += mn * min(a + r, m);
        src -= mn;
        dst -= mn;
        cans += src * r;
        cans += dst * a;
        ans = min(cans, ans);

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
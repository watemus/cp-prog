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


void run() {
    int n, c;
    cin >> n >> c;
    int cnt = 0;
    int tm = 0;
    vector<int> cs(n);
    for (int i = 0; i < n; i++) {
        cin >> cs[i];
        cin >> tm;
        cnt += cs[i];
    }
    sort(all(cs));
    int all = tm * n;
    int ans = 0;
    int psum = 0;
    int i = 0;
    while (i < n && psum + cs[i] <= all) {
        psum += cs[i];
        ans++;
        i++;
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
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

int calc(vector<int> p, vector<int> a, vector<int> b, int mask) {
    vector<int> na(3), nb(3);
    for (int i = 0; i < 3; i++) {
        na[i] = a[p[i]];
        nb[i] = b[p[i]];
        if (mask & (1 << i)) swap(na[i], nb[i]);
    }
    int ma = *max_element(all(na));
    int mb = *max_element(all(nb));
    int sa = accumulate(all(na), 0);
    int sb = accumulate(all(nb), 0);
    int ans = INFL;
    ans = min(ans, sa * mb);
    ans = min(ans, sb * ma);
    ans = min(ans, max(na[0], na[1] + na[2]) * (nb[0] + max(nb[1], nb[2])));
    return ans;
}

void run() {
    vector<int> p = {0, 1, 2};
    vector<int> a(3), b(3);
    for (int i : {0, 1, 2}) {
        cin >> a[i] >> b[i];
    }
    int ans = INFL;
    do {
        for (int mask = 0; mask < (1 << 3); mask++) {
            ans = min(ans, calc(p, a, b, mask));
        }
    } while (next_permutation(all(p)));
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
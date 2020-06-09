//
// Created by watemus on 04.06.2020.
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 1e6 + 228;

int all[MAXN];

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MOD3 = 998244353;

int pw(int a, int b, int MOD) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans *= a;
            ans %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return ans;
}

void run() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i =0; i < n; i++) {
        cin >> a[i];
    }
    sort(rall(a));
    int ans = 0, ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (ans == 0 && ans1 == 0 && ans2 == 0) {
            ans = pw(p, a[i], MOD1);
            ans1 = pw(p, a[i], MOD2);
            ans2 = pw(p, a[i], MOD3);
        } else {
            ans = (ans - pw(p, a[i], MOD1) + MOD1) % MOD1;
            ans1 = (ans1 - pw(p, a[i], MOD2) + MOD2) % MOD2;
            ans2 = (ans2 - pw(p, a[i], MOD3) + MOD3) % MOD3;
        }
    }
    cout << ans << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


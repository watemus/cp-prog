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

constexpr int MOD = 1e9 + 7;

int pw(int a, int b) {
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
    int n;
    cin >> n;
    map<pair<int, int>, int> cnts;
    int cnt_z = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        int gc;
        if (x == 0 && y == 0) {
            cnt_z++;
            continue;
        } else {
            gc = gcd(abs(x), abs(y));
        }
        cnts[{x / gc, y / gc}]++;
    }
    int ans = 1;
    set<pair<int, int>> usd;
    for (auto [vec, cnt] : cnts) {
        auto [x, y] = vec;
        if (usd.count({x, y}))
            continue;
        usd.insert({x, y});
        usd.insert({-x, -y});
        usd.insert({-y, x});
        usd.insert({y, -x});
        int cans1 = (ans * pw(2, cnts[{x, y}] + cnts[{-x, -y}]) - ans + MOD) % MOD;
        int cans2 = (ans * pw(2, cnts[{-y, x}] + cnts[{y, -x}]) - ans + MOD) % MOD;
        ans = (ans + cans1 + cans2) % MOD;
    }
    cout << (ans - 1 + MOD + cnt_z) % MOD << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

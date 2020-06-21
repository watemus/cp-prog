//
// Created by watemus on 10.05.2020.
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

constexpr int MOD = 998244353;

int pw(int a, int b) {
    int ans = 1;
    while (b > 0) {
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

const int MAXN = 3e5;

int fact[MAXN];

int C(int n, int k) {
    return fact[n] * pw(fact[k], MOD - 2) % MOD * pw(fact[n - k], MOD - 2) % MOD;
}

void run() {
    int n, m, k;
    cin >> n >> m >> k;
    k++;
    fact[0] = fact[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    int adj = 1;
    int cnt = n - 1;
    int ans = 0;
    while (adj <= k) {
        int cur = m * pw(m - 1, cnt) % MOD;
        cur *= C(n - 1, cnt);
        cur %= MOD;
        ans += cur;
        ans %= MOD;
        adj++;
        cnt--;
    }
    cout << ans << "\n";
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
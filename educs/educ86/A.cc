//
// Created by watemus on 26.04.2020.
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
const int MOD = 998244353;

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

const int MAXN = 5e5;
int fact[MAXN];

int C(int n, int k) {
    return fact[n] * pw(fact[k], MOD - 2) % MOD * pw(fact[n - k], MOD - 2) % MOD;
}

void run() {
    int n;
    cin >> n;
    int k = 00;
    cin >> k;
    fact[0] = fact[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
    if (k >= n) {
        cout << 0;
    } else {
        int ans = 0;
        for (int i = 0; i <= (n - k); i++) {
            if (i % 2 == (n - k) % 2) {
                ans += C(n - k, i) * pw(i, n) % MOD;
                ans %= MOD;
            } else {
                ans -= C(n - k, i) * pw(i, n) % MOD;
                ans += MOD; 
                ans %= MOD;
            }
        }
        ans *= C(n, n - k);
        ans %= MOD;
        cout << (k == 0 ? ans : ans * 2) % MOD << endl;
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
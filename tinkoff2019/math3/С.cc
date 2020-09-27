//
// Created by watemus on 14.04.2020.
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

const int MOD = 239017;

int powm(int a, int b) {
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

void run() {
    vector<int> fact(MOD + 10);
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < MOD + 10; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
    int times = 0;
    cin >> times;
    while (times--) {
        int n, k;
        cin >> n >> k;
        vector<int> ns, ks;
        while (n > 0) {
            ns.push_back(n % MOD);
            n /= MOD;
        }
        while (k > 0) {
            ks.push_back(k % MOD);
            k /= MOD;
        }
        while (ks.size() < ns.size()) ks.push_back(0);
        int ans = 1;
        for (int i = 0; i < ns.size(); i++) {
            int ni = ns[i];
            int ki = ks[i];
            if (ki > ni) {
                ans = 0;
                break;
            }
            ans = ans * fact[ni] % MOD * powm(fact[ki], MOD - 2) % MOD * powm(fact[ni - ki], MOD - 2) % MOD;
        }
        cout << ans << '\n';
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
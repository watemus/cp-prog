//
// Created by watemus on 10.04.2020.
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

const int MAXN = 3e5;

vector<int> divs;
vector<int> fact;

const int MOD = 998244353;

int bpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans *= a;
            ans %= MOD;
            b--;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return ans;
}

int len(int a) {
    map<int, int> cnt;
    int t = 0;
    for (auto d : divs) {
        if (a % d == 0) {
            cnt[d]++;
            t++;
            a /= d;
        }
    }
    int ans = fact[t];
    for (auto [x, y] : cnt) {
        ans = (ans * bpow(fact[y], MOD - 2)) % MOD;
    }
    return ans;
}

void run() {
    int D;
    cin >> D;
    int cd = D;
    for (int i = 2; i * i <= D; i++) {
        while (cd % i == 0) {
            divs.push_back(i);
            cd /= i;
        }
    }
    if (cd > 1) {
        divs.push_back(cd);
    }
    fact.resize(100);
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < 100; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    int n;
    cin >> n;
    while(n--) {
        int u, v;
        cin >> u >> v;
        int gc = gcd(u, v);
        int ans = (len(u / gc) * len(v / gc)) % MOD;
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
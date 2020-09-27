//
// Created by watemus on 15.04.2020.
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

int powm(int a, int b, int m) {
    int ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
            ans %= m;
        }
        a *= a;
        a %= m;
        b >>= 1;
    }
    return ans;
}

mt19937 rnd;

bool is_prime(int n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= min(1000LL, n - 1); i++) {
        if (n % i == 0) return false;
    }
    if (n <= 1'000'000) return true;
    int q = n - 1;
    int s = 0;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }
    for (int _ = 0; _ < 1000; _++) {
        int a = rnd() % (n - 2) + 2;
        int t = powm(a, q, n);
        if (t == 1 || t == n - 1) continue;
        bool f = false;
        int cr = 1;
        for (int i = 0; i < s - 1; i++) {
            t *= t;
            t %= n;
            if (t == n - 1) {
                f = true;
                break;
            }
        }
        if (f) continue;
        return false;
    }
    return true;
}

void run() {
    int n;
    cin >> n;
    cout << (is_prime(n) ? "YES\n" : "NO\n");
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
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

int phi(int n) {
    int ans = 0;
    int tn = n;
    for (int i = 2; i * i <= n; i++) {
        int cr = 1;
        while (tn % i == 0) {
            cr *= i;
            tn /= i;
        }
        if (cr > 1) {
            ans += cr - cr / i;
        }
    }
    if (tn > 1) {
        ans += tn - 1;
    }
    return ans;
}

vector<int> factor(int n) {
    vector<int> ans;
    int tn = n;
    for (int i = 2; i * i <= n; i++) {
        while (tn % i == 0) {
            ans.push_back(i);
            tn /= i;
        }
    }
    if (tn > 1) {
        ans.push_back(tn);
    }
    ans.resize(unique(all(ans)) - ans.begin());
    return ans;
}

inline int powm(int a, int b, int p) {
    int ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans *= a;
            ans %= p;
            b--;
        } else {
            a *= a;
            a %= p;
            b >>= 1;
        }
    }
    return ans;
}

bool is_prime(int a) {
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) return false;
    }
    return true;
}

void run() {
    int n;
    cin >> n;
    switch(n) {
        case 1:
            cout << 0;
            return;
        case 2:
            cout << 1;
            return;
        default:
            break;
    }
    int tn = n;
    if (tn % 2 == 0) tn >>= 1;
    if (!is_prime(tn)) {
        cout << -1;
        return;
    }
    int ph = phi(n);
    auto divs = factor(ph);
    for (int i = 2; i < n; i++) {
        bool f = true;
        for (auto d : divs) {
            int rs = powm(i, ph/d, n);
            if (rs == 1) {
                f = false;
                break;
            }
        }
        if (f) {
            cout << i << '\n';
            return;
        }
    }
    cout << -1;
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
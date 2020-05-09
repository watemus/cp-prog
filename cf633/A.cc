//
// Created by watemus on 12.04.2020.
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

const int MAXN = 2e5;

int fnd1(int n) {
    if (n == 0) return 1;
    int cur = 0;
    int st = 1;
    int c = 1;
    while (cur + st <= n) {
        cur += st;
        st *= 4;
    }
    return st + n - cur;
}

int fnd2(int n) {
    int st = 0;
    int ans = 0;
    if (n == 0) return 2;
    while (n) {
        if (n % 4 == 0) {
            ans += (1LL << st);
        } else if (n % 4 == 1) {
            ans += 0;
        } else if (n % 4 == 2) {
            ans += (1LL << st + 1);
        } else {
            ans += (1LL << st + 1) + (1 << st);
        }
        n /= 4;
        st += 2;
    }
    ans += (1LL << st + 1);
    return ans;
}

void run() {
    int n;
    cin >> n;
    if (n % 3 == 1) {
        cout << fnd1(n / 3);
    } else if (n % 3 == 2) {
        cout << fnd2(n / 3);
    } else {
        cout << (fnd1((n - 1) / 3) ^ fnd2((n - 1) / 3));
    }
    cout << '\n';
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
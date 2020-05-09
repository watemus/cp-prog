//
// Created by watemus on 07.05.2020.
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
constexpr int MAX = 100;
#else
constexpr int MAX = 3e7;
#endif

int n, a, b, c, m;

int descent(int dep, int v, int alpha, int beta) {
    if (dep == n)
        return (a * v % m * v + b * v + c) % m;
    if (dep % 2 == 0) {
        int value = -INFL;
        value = max(value, descent(dep + 1, v, alpha, beta));
        alpha = max(alpha, value);
        if (alpha >= beta)
            return value;
        value = max(value, descent(dep + 1, v + (1LL << (n - dep - 1)), alpha, beta));
        alpha = max(alpha, value);
        return value;
    } else {
        int value = INFL;
        value = min(value, descent(dep + 1, v, alpha, beta));
        beta = min(beta, value);
        if (alpha >= beta)
            return value;
        value = min(value, descent(dep + 1, v + (1LL << (n - dep - 1)), alpha, beta));
        beta = min(beta, value);
        return value;
    }
}

void run() {
    cin >> n;
    cin >> a >> b >> c;
    cin >> m;
    cout << descent(0, 0, -INFL, INFL);
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
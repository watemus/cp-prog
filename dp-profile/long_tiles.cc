//
// Created by watemus on 30.03.2020.
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
using ull = unsigned long long;
using ld = long double;
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

const ull MOD = 1e9 + 7;
const ull MAXN = 30;
const ull MAXM = 9;

int dp[MAXN][MAXM][1ULL << (MAXM * 2)];

enum {
    VERT = 0,
    HOR1 = 1,
    HOR2 = 2,
};

void run() {
    int n, m;
    cin >> m >> n;
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
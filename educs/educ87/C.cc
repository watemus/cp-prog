//
// Created by watemus on 17.05.2020.
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


void run() {
    cout << fixed << setprecision(12);
    int n;
    cin >> n;
    ld a = 1.0 /  (2 * sin(acos(-1) / ld(n * 2))) * 2;
    a *= a;
    ld c = sqrt(a - 1);
    ld angle2 = ld(n-1)/n * acos(-1) / 2;
    cout << c * sin(angle2) + sin(acos(-1)/2-angle2) << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
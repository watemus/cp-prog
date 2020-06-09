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
    ld h, m, a, b;
    cout << fixed << setprecision(12);
    cin >> a >> b >> h >> m;
    ld x1 = a*  sin(h / 12.0 * 2 * acos(-1));
    ld y1 = a * cos(h / 12.0 * 2 * acos(-1));
    ld x2 = b * sin(m / 60.0 * 2 * acos(-1));
    ld y2 = b * cos(m / 60.0 * 2 * acos(-1));
    cout << sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 -y2));
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
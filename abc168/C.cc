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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif


void run() {
    ld a, b, h, m;
    cin >> a >> b >> h >> m;
    ld angle_h = (h * 60 + m) / (60 * 12) * 2 * PI;
    ld angle_m = (m) / 60 * 2 * PI;
    ld x1 = a * cos(angle_h);
    ld y1 = a * sin(angle_h);
    ld x2 = b * cos(angle_m);
    ld y2 = b * sin(angle_m);
    cout << sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
//
// Created by watemus on 28.05.2020.
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

int h, c, t;
int ansa, ansb;
ld get(int a, int b) {
    return fabs(ld(h*a+c*b)/(a+b) - t);
}
void chkans(int a, int b) {
    ld geta = get(a, b);
    ld getb = get(ansa, ansb);
    if (geta < getb) {
        ansa = a;
        ansb = b;
    }
}

void run() {
    cin >> h >> c >> t;
    if (h - 2 * t + c == 0) {
        cout << 2 << '\n';
        return;
    }
    ansa = ansb = 2;
    chkans(1, 1);
    if (h == t) {
        cout << 1 << '\n';
        return;
    }
    int LL = 1;
    int RR = INFI;
    while (LL + 10 < RR) {
        int m1 = (LL + RR) / 2 - 10;
        int m2 = (LL + RR) / 2 + 10;
        ld gt1 = get(m1, m1 - 1);
        ld gt2 = get(m2, m2 - 1);
        if (gt1 > gt2) {
            LL = m1;
        } else {
            RR = m2;
        }
    }
    for (int i = LL; i <= RR; i++) {
        chkans(i, i - 1);
    }
    cout << ansa + ansb << '\n';
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
//
// Created by watemus on 27.03.2020.
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

bool ask(int lb, int rb) {
    cout << lb << ' ' << rb << endl;
    string s;
    cin >> s;
    return s == "Yes" || s == "1";
}

void run() {
    mt19937 rnd(time(nullptr));
    int n, k;
    int q;
    cin >> n >> k;
    int lb = 1;
    int rb = n;
    while (true) {
        if (rb - lb + 1 > 4 * k + 3) {
            int mid = (rb + lb) / 2;
            if (ask(lb, mid)) {
                lb = max(1LL, lb - k);
                rb = min(n, mid + k);
            } else {
                lb = max(1LL, mid - k);
                rb = min(n, rb + k);
            }
        } else {
            int t =  rnd() % (rb - lb + 1);
            if (ask(lb + t, lb + t)) return;
            else {
                lb = max(1LL, lb - k);
                rb = min(n, rb + k);
            }
        }
    }
}

signed main() {
#ifdef LOCAL
   // freopen("input.txt", "r", stdin);
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
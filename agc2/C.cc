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
#else
#endif


void run() {
    int n, L;
    cin >> n >> L;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        if (a[i] + a[i + 1] >= L) {
            cout << "Possible\n";
            for (int j = 0; j < i; j++) {
                cout << j + 1 << '\n';
            }
            for (int j = n - 2; j > i; j--) {
                cout << j + 1 << '\n';
            }
            cout << i + 1 << '\n';
            return;
        }
    }
    cout << "Impossible\n";
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
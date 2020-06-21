//
// Created by watemus on 31.05.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;
const int INFL = 1e9 + 9;


void run() {
    int n;
    cin >> n;
    int odd, even;
    odd = even = 0;
    int x;
    cin >> x;
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;
        if (el % 2) odd++;
        else even++;
    }
    if (odd == 0) {
        cout << "No\n";
        return;
    }
    int cx = x - 1;
    odd--;
    while (odd >= 2 && cx >= 2) {
        odd -= 2;
        cx -= 2;
    }
    while (cx > 0 && even > 0) {
        cx--;
        even--;
    }
    if (cx ==0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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
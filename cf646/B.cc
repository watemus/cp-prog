//
// Created by watemus on 31.05.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void run() {
    string s;
    cin >> s;
    int n = s.size();
    if (n == 1) {
        cout << 0 << "\n";
        return;
    }
    vector<int> cnt0(n), cnt1(n);
    vector<int> cnt0s(n ), cnt1s(n);
    cnt0[0] = s[0] == '0';
    cnt1[0] = s[0] == '1';
    cnt0s[n - 1] = s[n - 1] == '0';
    cnt1s[n - 1] = s[n - 1] == '1';
    for (int i = 1; i < n; i++) {
        cnt0[i] = cnt0[i - 1] + (s[i] == '0');
        cnt1[i] = cnt1[i - 1] + (s[i] == '1');
    }
    for (int i = n - 2; i >= 0; i--) {
        cnt0s[i] = cnt0s[i + 1] + (s[i] == '0');
        cnt1s[i] = cnt1s[i + 1] + (s[i] == '1');
    }
    int ans = INF;
    for(int i = 0; i < n - 1; i++) {
        ans = min(ans, min(cnt0[i], cnt1[i]) + min(cnt0s[i + 1], cnt1s[i + 1]));
    }
    cout << ans << '\n';
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
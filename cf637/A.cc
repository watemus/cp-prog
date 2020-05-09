//
// Created by watemus on 23.04.2020.
//..

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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif

int can(string &s, string &t) {
    int ans = 0;
    for (int i = 0; i < 7; i++) {
        if (s[i] == '0' && t[i] == '1') ans++;
        if (s[i] == '1' && t[i] == '0') return -1;
    }
    return ans;
}

void run() {
    string s;
    map<string, int> to = {{string("1110111"), 0}, {"0010010", 1}, {"1011101", 2}, {"1011011", 3}, {"0111010", 4}, {"1101011", 5}, {"1101111", 6}, {"1010010", 7}, {"1111111", 8}, {"1111011", 9}};
    map<int, string> from;
    set<string> hs = {};
    for (auto [x, y] : to) {
        from[y] = x;
    }
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(n + 10, vector<int>(k + 10, -1));
    dp[0][0] = 0;
    vector<int> a;
    vector<string> sa;
    n *= 7;
    for (int i = 0; i < n; i += 7) {
        string cr;
        cin >> cr;
        sa.push_back(cr);
        a.push_back(to[cr]);
    }
    reverse(all(sa));
    reverse(all(a));
    for (int i = 1; i <= n/7; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i - 1][j] == -1) continue;
            string f = sa[i - 1];
            for (int h = 0; h < 10; h++) {
                string t = from[h];
                int cn = can(f, t);
                if (cn != -1) {
                    dp[i][j + cn] = max(dp[i][j + cn], h);
                }
            }
        }
    }
    if (dp[n/7][k] == -1) {
        cout << "-1\n";
    } else {
        int cr = k;
        string ans;
        for (int i = n/7; i >= 1; i--) {
            ans += to_string(dp[i][cr]);
            cr -= can(sa[i - 1], from[dp[i][cr]]);
        }
        cout << ans << '\n';
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
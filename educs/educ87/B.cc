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
    string s;
    cin >> s;
    map<char, int> prv;
    prv['1'] = prv['2'] = prv['3'] = -1;
    int ans = INFL;
    for (int i = 0; i < s.size(); i++) {
        char cr = s[i];
        prv[cr] = i;
        if (prv['1'] == -1 || prv['2'] == -1 || prv['3'] == -1) {
            continue;
        }
        int len = max({i - prv['1'] + 1, i - prv['2'] + 1, i - prv['3'] + 1});
        ans = min(len, ans);
    }
    cout << (ans == INFL ? 0 : ans) << '\n';
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
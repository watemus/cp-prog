//
// Created by watemus on 08.04.2020.
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

constexpr int MAXN = 1e6;

int t[MAXN];

void run() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<vector<int>> ans;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        ans.push_back({});
        for (int j = 0; j < n - 1; j++) {
            if (s[j] == 'R' && s[j + 1] == 'L') {
                ans.back().push_back(j + 1);
                cnt++;
            }
        }
        for (auto el : ans.back()) {
            swap(s[el], s[el -1]);
        }
        if (ans.back().size() == 0) {
            ans.pop_back();
            break;
        }
    }
    if (cnt < k || ans.size() > k) {
        cout << "-1\n";
        return;
    }
    int cr = ans.size();
    vector<vector<int>> cans;
    for (auto &row : ans) {
        cans.push_back({});
        int i = 0;
        for (auto el : row) {
            cans.back().push_back(el);
            if (cr < k && i != row.size() - 1) {
                cr++;
                cans.push_back({});
            }
        }
        if (cans.back().size() == 0) cans.pop_back();
    }
    for (auto &row : cans) {
        cout << row.size() << ' ';
        for (auto el : row) {
            cout << el << ' ';
        }
        cout << '\n';
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
//
// Created by watemus on 03.05.2020.
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

vector<vector<int>> usd;

void dfs(int x, int y, vector<vector<char>> &a, int n, int m) {
    if (usd[x][y]) return;
    usd[x][y] = 1;
    if (x > 0 && a[x - 1][y] == '#') dfs(x - 1, y, a, n, m);
    if (x < n - 1 && a[x + 1][y] == '#') dfs(x + 1, y, a, n, m);
    if (y > 0 && a[x][y - 1] == '#') dfs(x, y - 1, a, n, m);
    if (y < m - 1 && a[x][y + 1] == '#') dfs(x, y + 1, a, n, m);
}

void run() {
    int n, m;
    cin >> n >> m;
    usd.resize(n, vector<int>(m, 0));
    vector<vector<char>> a(n, vector<char>(m));
    int cntb = 0;
    vector<int> cnt_row(n), cnt_col(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '#') {
                cnt_col[j]++;
                cnt_row[i]++;
                cntb++;
            }
        }
    }
    if (!cntb) {
        cout << 0 << endl;
        return;
    }
    int cnt1 = -1, cnt2 = -1;
    for (int i = 0; i < n; i++) {
        if (!cnt_row[i]) {
            cnt1 = 1;
        }
    }
    for (int i = 0; i < m; i++) {
        if (!cnt_col[i]) {
            cnt2 = 1;
        }
    }
    if (cnt1 * cnt2 < 0) {
        cout << -1 << endl;
        return;
    }
    char prev = '.';
    for (int i = 0; i < n; i++) {
        prev = '.';
        bool was = false;
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#' && prev == '.') {
                if (was) {
                    cout << -1 << endl;
                    return;
                } else {
                    was = true;
                }
                prev = a[i][j];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        prev = '.';
        bool was = false;
        for (int j = 0; j < n; j++) {
            if (a[j][i] == '#' && prev == '.') {
                if (was) {
                    cout << -1 << endl;
                    return;
                } else {
                    was = true;
                }
            }
            prev = a[j][i];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#' && !usd[i][j]) {
                dfs(i, j, a, n, m);
                ans++;
            }
        }
    }
    cout << ans << endl;
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

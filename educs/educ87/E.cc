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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 5e3 + 10;

vector<int> g[MAXN];

int clr[MAXN], usd[MAXN], comp[MAXN];
int cnt_clr[3];
int cnt_comp = 0;

void check_bi(int v, int cl) {
    usd[v] = 1;
    clr[v] = cl;
    cnt_clr[cl]++;
    comp[v] = cnt_comp;
    for (auto u : g[v]) {
        if (clr[v] == clr[u]) {
            cout << "NO\n";
            exit(0);
        }
        if (!usd[u]) check_bi(u, 3 - cl);
    }
}

int dp[MAXN][MAXN];
int ans_comp[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(usd, 0, sizeof usd);
    memset(clr, 0, sizeof clr);
    vector<pair<int, int>> cnt;
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            cnt_clr[1] = cnt_clr[2] = 0;
            check_bi(i, 1);
            cnt.emplace_back(cnt_clr[1], cnt_clr[2]);
            cnt_comp++;
        }
    }
    for (int i = 0; i < n; i++) {
        memset(dp[i], -1, sizeof dp[i]);
    }
    dp[0][0] = 0;
    for (int i = 0; i < cnt_comp; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] != -1) {
                dp[i + 1][j + cnt[i].first] = 1;
                dp[i + 1][j + cnt[i].second] = 2;
            }
        }
    }
    if (-1==dp[cnt_comp][n2]) {
        cout << "NO\n";
        return;
    }
    memset(ans_comp, 0, sizeof ans_comp);
    int level = n2;
    for (int i = cnt_comp; i > 0; i--) {
        ans_comp[i - 1] = dp[i][level];
        if (ans_comp[i - 1] == 1) {
            level -= cnt[i - 1].first;
        } else {
            level -= cnt[i - 1].second;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        if (!(ans_comp[comp[i]] == clr[i])) {
            if (n1 > 0) {
                cout << 1;
                n1--;
            } else {
                cout << 3;
            }
        } else {
            cout << 2;
        }
    }
    cout << '\n';
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
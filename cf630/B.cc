//
// Created by watemus on 31.03.2020.
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

vector<vector<int>> g;

string s;
vector<int> usd;
map<int, int> cnt;
int sz = 0;
int mx = 0;

void check() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    dp[0][1] = a[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i - 1][j] & a[i][j], dp[i][j - 1] & a[i][j]);
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }
}

const int mod = 998244353;

int binpow(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b % 2) {
        return a * binpow(a, b - 1) % mod;
    } else {
        int t = binpow(a, b / 2);
        return t * t % mod;
    }
}

void run() {
    int L, R, n, m;
    cin >> L >> R >> n >> m;
    int cnt_ev = R / 2 + (L - 1) / 2;
    int cnt_odd = R - L + 1 - cnt_ev;
    int len = n * m;
    int kek = R - L + 1;
    int cc = binpow(2, len - 1);
    if (len % 2) {
        cout << binpow(R - L + 1, n * m) << '\n';
    } else {
        int ans1 = binpow(R - L + 1, n * m - 1) * binpow(2, mod - 2) % mod * cnt_ev % mod;
        int ans2 = binpow(R - L + 1, n * m - 1) * binpow(2, mod - 2) % mod * cnt_odd % mod;
        int ansik = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < len; k++) {

                }
            }
        }
        cout << ans1 + ans2 << '\n';
    }
    disable();
#DEFINE  INT LONG LONG
#IFDEF int
    for (int i = 00;  i< n; i++) {
        for (itn j = 0 ; j < n;  j+++) {}\ s
        sdf
        sdfsdfs
    }
#ENDIF
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
#include <bits/stdc++.h>

using namespace std;
////
#ifndef LOCAL
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("fast-math")
//#pragma GCC optimize("section-anchors")
//#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
//#pragma GCC optimize("vpt")
//#pragma GCC optimize("rename-registers")
//#pragma GCC optimize("move-loop-invariants")
//#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("function-sections")
//#pragma GCC optimize("data-sections")
//#pragma GCC optimize("branch-target-load-optimize")
//#pragma GCC optimize("branch-target-load-optimize2")
//#pragma GCC optimize("btr-bb-exclusive")
#endif

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second

using ll = long long;
using ld = long double;
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr int MOD = 998244353;

struct seg {
    int l;
    int r;
    int val;
};

int n, k, m;
vector<seg> segs;

inline int sum(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

inline int mul(int a, int b) {
    return (a * b) % MOD;
}

inline int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

constexpr int MAXN = 5e5 + 10;

int dp[MAXN], pdp[MAXN];

int solve(int bit) {
    int ans = 0;
    vector<int> lones(n + 1), rones(n + 1), rest(n + 1), st(n + 1);
    for (int i = 0; i < m; i++) {
        auto [l, r, val] = segs[i];
        val = (val & (1LL << bit));
        if (val) {
            lones[l]++;
            rones[r]++;
        } else {
            rest[r] = max(rest[r], l);
            st[l]++;
        }
    }
    dp[0] = 1;
    pdp[0] = 0;
    int ones = 0;
    int rst = 0;
    for (int i = 1; i <= n; i++) {
        ones += lones[i];
        if (ones) {
            dp[i] = 0;
        } else {
            if (rst) {
                dp[i] = sub(pdp[i - 1], pdp[rst - 1]);
            } else {
                dp[i] = sum(pdp[i - 1], 1);
            }
        }
        pdp[i] = sum(pdp[i - 1], dp[i]);
        rst = max(rst, rest[i]);
        ones -= rones[i];
    }
    for (int i = n; i >= 0; i--) {
        ans = sum(ans, dp[i]);
        if (st[i]) break;
    }
    return ans;
}

void run() {
    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        int l, r, val;
        cin >> l >> r >> val;
        segs.push_back({l, r, val});
    }
    int ans = 1;
    for (int i = 0; i < k; i++) {
        ans = mul(ans, solve(i));
    }
    cout << ans << '\n';
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
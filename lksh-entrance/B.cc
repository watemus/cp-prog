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
const int MAXN = 1000;
const int BLOCK_SIZE = 100;
#else
const int MAXN = 3e5 + 10;
const int BLOCK_SIZE = 500;
#endif

const int MOD = 998244353;

inline int sum(int lhs, int rhs) {
    lhs += rhs;
    if (lhs >= MOD) lhs -= MOD;
    return lhs;
}

inline int sub(int lhs, int rhs) {
    lhs = lhs - rhs + MOD;
    if (lhs >= MOD) lhs -= MOD;
    return lhs;
}

inline int mul(int lhs, int rhs) {
    return (lhs * rhs) % MOD;
}

struct Solver {
    int dp[MAXN];
    int mask[MAXN];
    int block_mask[MAXN];
    int block_sum[MAXN];
    int block_mask_sum[MAXN];
    Solver() {
        memset(dp, 0, sizeof dp);
        memset(mask, 0, sizeof mask);
        memset(block_mask, 0, sizeof block_mask);
        memset(block_sum, 0, sizeof block_sum);
        memset(block_mask_sum, 0, sizeof block_mask_sum);
    }
    void set_dp(int pos, int val) {
        dp[pos] = val;
        block_sum[pos / BLOCK_SIZE] = sum(block_sum[pos / BLOCK_SIZE], val);
        if (mask[pos] || block_mask_sum[pos]) {
            block_mask_sum[pos / BLOCK_SIZE] = sum(block_mask_sum[pos / BLOCK_SIZE], val);
        }
    }
    void add_mask(int lb, int rb) {
        while (lb <= rb && lb % BLOCK_SIZE != 0) {
            if (!mask[lb])
                block_mask_sum[lb / BLOCK_SIZE] = sum(block_mask_sum[lb / BLOCK_SIZE], dp[lb]);
            mask[lb]++;
            lb++;
        }
        while (lb + BLOCK_SIZE < rb) {
            block_mask[lb / BLOCK_SIZE]++;
            lb += BLOCK_SIZE;
        }
        while (lb <= rb) {
            if (!mask[lb]) {
                block_mask_sum[lb / BLOCK_SIZE] = sum(block_mask_sum[lb / BLOCK_SIZE], dp[lb]);
            }
            mask[lb]++;
            lb++;
        }
    }
    void rem_mask(int lb, int rb) {
        while (lb <= rb && lb % BLOCK_SIZE != 0) {
            mask[lb]--;
            if (!mask[lb]) {
                block_mask_sum[lb / BLOCK_SIZE] = sub(block_mask_sum[lb / BLOCK_SIZE], dp[lb]);
            }
            lb++;
        }
        while (lb + BLOCK_SIZE < rb) {
            block_mask[lb / BLOCK_SIZE]--;
            lb += BLOCK_SIZE;
        }
        while (lb <= rb) {
            mask[lb]--;
            if (!mask[lb]) {
                block_mask_sum[lb / BLOCK_SIZE] = sub(block_mask_sum[lb / BLOCK_SIZE], dp[lb]);
            }
            lb++;
        }
    }
    int get_prefix_dp(int rb) {
        int lb = 0;
        int ans = 0;
        while (lb + BLOCK_SIZE < rb) {
            if (block_mask[lb / BLOCK_SIZE]) {
                ans = sum(ans, block_sum[lb / BLOCK_SIZE]);
            } else {
                ans = sum(ans, block_mask_sum[lb / BLOCK_SIZE]);
            }
            lb += BLOCK_SIZE;
        }
        while (lb <= rb) {
            if (block_mask[lb / BLOCK_SIZE] || mask[lb]) {
                ans = sum(ans, dp[lb]);
            }
            lb++;
        }
        return ans;
    }
};

void run() {
    int n;
    cin >> n;
    Solver solver;
    solver.set_dp(0, 1);
    vector<int> prev1(n + 10), prev2(n + 10), used(n + 10);
    for (int i = 1; i <= n; i++) {
        int elem;
        cin >> elem;
        if (used[elem]) {
            solver.rem_mask(prev1[elem], prev2[elem]);
            prev1[elem] = prev2[elem] + 1;
            prev2[elem] = i - 1;
        } else {
            used[elem] = 1;
            prev2[elem] = i - 1;
        }
        solver.add_mask(prev1[elem], prev2[elem]);
        solver.set_dp(i, solver.get_prefix_dp(i - 1));
    }
    cout << solver.dp[n] << '\n';
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
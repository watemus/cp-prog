//
// Created by watemus on 30.03.2020.
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

enum {
    BLOCK = 0,
    TILE_VERT = 1,
    TILE_HOR1 = 2,
    TILE_HOR2 = 3,
};

const int MASK = 16;
const int BLOCKS = 4;
const int MOD = 1e9 + 7;

void run() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> blocks(n + 1, {0, 0});
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        blocks[x - 1][y - 1] = 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(MASK));
    for (int msk = 0; msk < MASK; msk++) {
        int fst = msk % BLOCKS;
        int scd = msk / BLOCKS;
        if ((fst != BLOCK) && blocks[0][0]) continue;
        if ((scd != BLOCK) && blocks[0][1]) continue;
        if ((fst == TILE_VERT) != (scd == TILE_VERT)) continue;
        if (fst == TILE_HOR2 || scd == TILE_HOR2) continue;
        dp[0][msk] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int msk = 0; msk < MASK; msk++) {
            int fst = msk % BLOCKS;
            int scd = msk / BLOCKS;
            if ((fst != BLOCK) && blocks[i][0]) continue;
            if ((scd != BLOCK) && blocks[i][1]) continue;
            if ((fst == TILE_VERT) != (scd == TILE_VERT)) continue;
            for (int pmsk = 0; pmsk < MASK; pmsk++) {
                int pfst = pmsk % BLOCKS;
                int pscd = pmsk / BLOCKS;
                if ((pfst == TILE_HOR1) != (fst == TILE_HOR2)) continue;
                if ((pscd == TILE_HOR1) != (scd == TILE_HOR2)) continue;
                dp[i][msk] += dp[i - 1][pmsk];
                dp[i][msk] %= MOD;
            }
        }
    }
    int ans = 0;
    for (int msk = 0; msk < MASK; msk++) {
        int fst = msk % BLOCKS;
        int scd = msk / BLOCKS;
        if ((fst != BLOCK) && blocks[n - 1][0]) continue;
        if ((scd != BLOCK) && blocks[n - 1][1]) continue;
        if ((fst == TILE_VERT) != (scd == TILE_VERT)) continue;
        if (fst == TILE_HOR1 || scd == TILE_HOR1) continue;
        ans += dp[n - 1][msk];
        ans %= MOD;
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
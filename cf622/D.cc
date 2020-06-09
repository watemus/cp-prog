//
// Created by watemus on 06.06.2020.
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

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename T1, typename T2>
using umap = unordered_map<T1, T2>;

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n, m, k;
    cin >> n >> m >> k;
    vec<int> coords;
    coords.push_back(0);
    coords.push_back(m + 1);
    vec<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
        coords.push_back(segments[i].first);
        coords.push_back(segments[i].second);
    }
    sort(all(coords));
    coords.resize(unique(all(coords)) - coords.begin());
    map<int, int> to;
    for (int i = 0; i < coords.size(); i++) {
        to[coords[i]] = i;
    }
    vec<vec<int>> begins(coords.size()), ends(coords.size());
    for (int i = 0; i < n; i++) {
        begins[to[segments[i].first]].push_back(i);
        ends[to[segments[i].second]].push_back(i);
    }
    vec<vec<int>> dp(coords.size(), vec<int>(1 << k));
    vec<int> id2k(n);
    int cur = 0;
    vec<int> used(k);
    int ans = 0;
    for (int i = 1; i < coords.size() - 1; i++) {
        int cmask = 0;
        for (auto id : begins[i]) {
            while (used[cur]) {
                cur++;
                cur %= k;
            }
            cmask += (1 << cur);
            id2k[id] = cur;
            used[cur] = 1;
        }
        int bad = 0;
        for (auto id : ends[i]) {
            bad += (1 << id2k[id]);
        }
        auto sdp = dp[i];
        for (int mask = 0; mask < (1 << k); mask++) {
            int cnt1 = 0;
            int cnt2 = 0;
            for (int i = 0; i < k; i++) {
                if (!used[i] && (mask & (1 << i))) {
                    cnt1 = -1;
                    break;
                }
                if (bad & (1 << i)) cnt2++;
                if (mask & (1 << i)) cnt1++;
            }
            if (cnt1 == -1) continue;
            int pmask = mask - (mask & cmask);
            dp[i][mask] = sdp[pmask] + (cnt1 % 2) * (cnt2 == cnt1 ? 1 : coords[i + 1] - coords[i]);
            if (i + 1 < coords.size()) {
                dp[i + 1][mask - (mask & bad)] = max(dp[i + 1][mask - (mask & bad)], dp[i][mask]);
            }
            if (i == coords.size() - 2) {
                ans = max(ans, dp[i][mask]);
            }
        }
        for (auto id : ends[i]) {
            used[id2k[id]] = 0;
        }
    }
    cout << ans << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


//
// Created by watemus on 24.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

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
const ld PI = acos(-1);
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1e5 + 10;

vec<int> g[MAXN];
vec<int> col;
vec<vec<pair<int, int>>> queries;
vec<int> ans;
vec<map<int, int>> cnt_colors, cnt_cnt;

void merge(int u, int v) {
    if (cnt_colors[v].size() > cnt_colors[u].size()) {
        cnt_cnt[v].swap(cnt_cnt[u]);
        cnt_colors[v].swap(cnt_colors[u]);
    }
    for (auto [color, cnt] : cnt_colors[v]) {
        for (int i = 0; i < cnt; i++) {
            cnt_colors[u][color]++;
            cnt_cnt[u][cnt_colors[u][color]]++;
        }
    }
}

void dfs(int v, int p) {
    cnt_colors[v][col[v]]++;
    cnt_cnt[v][1]++;
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v);
            merge(v, u);
        }
    }
    for (auto [k, i] : queries[v]) {
        ans[i] += cnt_cnt[v][k];
    }
}

void run() {
    int n, q;
    cin >> n >> q;
    col.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> col[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queries.resize(n);
    cnt_colors.resize(n);
    cnt_cnt.resize(n);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        int v, k;
        cin >> v >> k;
        v--;
        queries[v].emplace_back(k, i);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
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


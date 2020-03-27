//
// Created by watemus on 26.03.2020.
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

constexpr int MAXN = 2e5 + 228;
constexpr int MAXK = 32;

int trie[2][MAXN * MAXK];
int cnt[MAXN * MAXK];
int vs[MAXN * MAXK];
int size_trie = 2;

int root = 1;

void add_num(ll a, int v) {
    int cur = root;
    cnt[root]++;
    for (int cbit = MAXK - 1; cbit >= 0; cbit--) {
        int bit = bool((1LL << cbit) & a);
        if (!trie[bit][cur]) {
            trie[bit][cur] = size_trie++;
        }
        cur = trie[bit][cur];
        cnt[cur]++;
    }
    vs[cur] = v;
}

vector<int> g[MAXN];

void dfs(int v, int p, vector<int> &c, vector<int> &usd) {
    c.push_back(v);
    for (auto u : g[v]) {
        if (u != p)
            dfs(u, v, c, usd);
    }
}

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        add_num(a[i], i);
    }
    int ans = 0;
    for (int iter = 0; iter < 20; iter++) {
        vector<int> usd(n);
        set<pair<int, int>> add_edges;
        for (int v = 0; v < n; v++) {
            if (!usd[v]) {
                vector<int> c;
                dfs(v, v, c, usd);
                if (c.size() == n) break;
            }
        }
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
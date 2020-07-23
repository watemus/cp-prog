//
// Created by watemus on 17.07.2020.
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
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    ll n, m;
    cin >> n >> m;
    vec<vec<ll>> g(n);
    vec<pair<ll, ll>> nor;
    for (ll i = 0; i < m; i++) {
        ll t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        if (t == 0) {
            nor.emplace_back(u, v);
        } else {
            g[u].push_back(v);
        }
    }
    vec<ll> tsort;
    vec<ll> usd(n);
    bool bad = false;
    function<void(int)> dfs = [&](int v) {
        usd[v] = 1;
        for (auto u : g[v]) {
            if (!usd[u])
                dfs(u);
            if (usd[u] == 1) {
                bad = true;
            }
        }
        usd[v] = 2;
        tsort.push_back(v);
    };
    for (ll i = 0; i < n; i++) {
        if (!usd[i]) dfs(i);
    }
    if (bad) {
        cout << "NO\n";
        return;
    }
    reverse(ALL(tsort));
    vec<ll> r_tsort(n);
    for (ll i = 0; i < n; i++) {
        r_tsort[tsort[i]] = i;
    }
    cout << "YES\n";
    for (ll i = 0; i < n; i++) {
        for (auto u : g[i]) {
            cout << i + 1 << ' ' << u + 1 << '\n';
        }
    }
    for (auto [u, v] : nor) {
        if (r_tsort[u] > r_tsort[v]) {
            cout << v + 1 << ' ' << u + 1 << '\n';
        } else {
            cout << u + 1 << ' ' << v + 1 << '\n';
        }
    }
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}



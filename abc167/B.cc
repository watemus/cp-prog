//
// Created by watemus on 10.05.2020.
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
int n, m;
vector<int> usd, dist, a;

void dfs(int v, int sv) {
    usd[v] = 1;
    if (a[v] == v) {
        dist[v] = 0;
    } else if (usd[v] == 1) {
        cout << v + 1 << endl;
        exit(0);
    } else if (usd[a[v]]) {
        dist[v] = dist[a[v]] + 1;
    } else {
        dfs(a[v], sv);
        dist[v] = dist[a[v]] + 1;
    }
    if (dist[v] >= m) {
        cout << v + 1 << endl;
        exit(0);
    }
    usd[v] = 2;
}

void run() {
    cin >> n >> m;
    a.resize(n);
    usd.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; i++) {
        if (!usd[i]) dfs(i, i);
    }
    cout << "-1\n";
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
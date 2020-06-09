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


void run() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vector<int> dist(n, -1);
    dist[0] = 0;
    int v = 0;
    bool on_cycle = false;
    while (k > 0) {
        if (dist[a[v]] != -1 && !on_cycle) {
            int len = dist[v] - dist[a[v]] + 1;
            k = (k - 1 + len) % len;
            on_cycle = true;
        } else {
            k--;
            if (dist[a[v]] == -1) {
                dist[a[v]] = dist[v] + 1;
            }
        }
        v = a[v];
    }
    cout << v + 1 << endl;
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
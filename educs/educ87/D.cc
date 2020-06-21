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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1 << 20;

int t[MAXN * 2 + 228];

void add(int v, int lb, int rb, int at,int dt) {
    if (rb - lb == 1) {
        t[v]+=dt;
        return;
    }
    int mid = (lb + rb) / 2;
    if (at < mid) add(v * 2 + 1, lb, mid, at, dt);
    else add(v * 2 + 2, mid, rb, at, dt);
    t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

int get(int v, int lb, int rb, int k) {
    if (rb - lb == 1) {
        return lb;
    }
    int lt = t[v * 2 + 1];
    int mid = (lb + rb) / 2;
    if (k > lt) {
        k -= lt;
        return get(v * 2 + 2, mid, rb, k);
    }
    return get(v * 2 + 1, lb, mid, k);
}

void run() {
    memset(t, 0, sizeof t);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        add(0, 0, MAXN, t, 1);
    }
    for (int i = 0; i < k; i++) {
        int el;
        cin >> el;
        if (el < 0) {
            int at = get(0, 0, MAXN, (-el));
            add(0, 0, MAXN, at, -1);
        } else {
            add(0, 0, MAXN, el, 1);
        }
    }
    int ans = get(0, 0, MAXN, 1);
    if (ans == MAXN - 1) {
        cout << "0\n";
    } else {
        cout << ans << '\n';
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
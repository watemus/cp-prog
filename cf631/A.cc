//
// Created by watemus on 03.04.2020.
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

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    int sm = 0;
    for (auto &el : a) {
        cin >> el;
        sm += el;
    }
    if (sm < n) {
        cout << -1;
        return;
    }
    vector<int> ans(m);
    int ost = n;
    vector<int> cst(m);
    for (int i = 0; i < m; i++) {
        ans[i] = n - i - a[i];
        ost = min(ost, n - i - a[i]);
        cst[i] = ost;
        if (n - i - a[i] < 0) {
            cout << -1;
            return;
        }
    }
    int ptr = 0;
    for (int i = m - 1; i >= 1; i--) {
        if (ost <= 0) break;
        ans[i] = ptr;
        ptr += a[i];
        ost = n - (n - cst[i - 1] + ptr);
    }
    if (ost > 0) {
        cout << -1;
        return;
    }
    for (auto el : ans) {
        cout << el + 1 << ' ';
    }
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
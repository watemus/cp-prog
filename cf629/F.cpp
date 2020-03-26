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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

const int MAXN = 5e5;

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        a.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        a.push_back(a[i]);
    }
    int st = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == a[i + 1]) {
            st = i;
        }
    }
    int prev = -1;
    vector<int> ans(n);
    int cl = 1;
    int cnt = 1;
    for (int i = st; i < st + n; i++) {
        if (a[i] != prev && prev != -1) {
            cl = 3 - cl;
            cnt = 2;
        }
        prev = a[i];
        ans[i % n] = cl;
    }
    if (ans[st] == ans[(st + n - 1) % n] && a[st] != a[st + n - 1]) {
        if (a[st + 1] == a[st]) {
            cnt = 2;
            ans[st] = 3 - ans[st];
        } else if (a[st + n - 1] == a[st + n - 2]) {
            cnt = 2;
            ans[(st + n - 1) % n] = 3 - ans[(st + n - 1) % n];
        } else {
            cnt = 3;
            ans[st] = 3;
        }
    }
    cout << cnt << '\n';
    for (auto el : ans) {
        cout << el << ' ';
    }
    cout << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
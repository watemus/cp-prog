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

inline int pr(int v) {
    return (v - 1) / 2;
}

inline int lt(int v) {
    return 2 * v + 1;
}

inline int rt(int v) {
    return 2 * v + 2;
}

vector<int> build(vector<int> &a, int h) {
    vector<int> usd(a.size());
    vector<int> ans;
    for (int i = 0; i < (1 << h); i++) {
        int bk = a.size() - i - 1;
        while (bk > 0 && max(a[lt(pr(bk))], a[rt(pr(bk))]) == a[bk])
            bk /= 2;
        ans.push_back(bk);
    }
    return ans;
}

void remove(int v, vector<int> &a) {
    if (lt(v) >= a.size()) {
        a[v] = 0;
    } else {
        if (a[rt(v)] > a[lt(v)]) {
            a[v] = a[rt(v)];
            remove(rt(v), a);
        } else {
            a[v] = a[lt(v)];
            remove(lt(v), a);
        }
    }
}

void run() {
    int h, g;
    cin >> h >> g;
    vector<int> a((1 << h) - 1);
    int n = (1 << h) - 1;
    int sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sm += a[i];
    }
    vector<int> ans;
    int ost = 0;
    while (h > g) {
        h--;
        vector<int> to_del = build(a, h);
        for (auto el : to_del) {
            ans.push_back(el + 1);
            ost += a[el];
            remove(el, a);
        }
        for (auto &el : to_del) {
            a.pop_back();
        }
    }
    cout << sm - ost << '\n';
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
//
// Created by watemus on 12.04.2020.
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

pair<vector<int>, vector<int>> build(vector<int> &s) {
    int n = s.size();
    vector<int> c(n), p(n);
    iota(all(p), 0);
    sort(all(p), [&s](int a, int b){
        return s[a] < s[b];
    });
    for (int i = 1; i < n; i++) {
        c[p[i]] = c[p[i - 1]];
        if (s[p[i - 1]] != s[p[i]]) {
            c[p[i]]++;
        }
    }
    int k = 0;
    while ((1 << k) < n) {
        vector<int> c_new(n), p_new(n), pos(n), cnt(n);
        for (int i = 0; i < n; i++) {
            p[i] = (p[i] - (1 << k) + n);
            if (p[i] >= n) p[i] -= n;
        }
        for (int i = 0; i < n; i++) {
            cnt[c[i]]++;
        }
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (int i = 0; i < n; i++) {
            p_new[pos[c[p[i]]]++] = p[i];
        }
        p = p_new;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            c_new[p[i]] = c_new[p[i - 1]];
            if (cur != prev) {
                c_new[p[i]]++;
            }
        }
        c = c_new;
        k++;
    }
    return {p, c};
}

const int MAXN = 1e3;

vector<int> t[MAXN * 4];

void build(int v, int tl, int tr) {
    if (tr - tl == 1) {
        int k;
        cin >> k;
        t[v].resize(k);
        for (auto &el : t[v]) cin >> el;
    } else {
        int mid = tl + tr >> 1;
        build(v * 2 + 1, tl, mid);
        build(v * 2 + 2, mid, tr);
        int i = 0;
        int j = 0;
        while (i < t[v * 2 + 1].size() && j < t[v * 2 + 2].size()) {
            if (t[v * 2 + 1][i] < t[v * 2 + 2][j]) {
                t[v].push_back(t[v * 2 + 1][i++]);
            } else {
                t[v].push_back(t[v * 2 + 2][j++]);
            }
        }
        while (i < t[v * 2 + 1].size()) {
            {
                t[v].push_back(t[v * 2 + 1][i++]);
            }
        }
        while (j < t[v * 2 + 2].size()) {
            {
                t[v].push_back(t[v * 2 + 2][j++]);
            }
        }
    }
}

void run() {
    int n;
    cin >> n;
    build(0, 0, n);
    for (auto u : t[0]) {
        cout << u << ' ';
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
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
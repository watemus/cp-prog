//
// Created by watemus on 26.04.2020.
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
const int K = 4;
#else
const int K = 500;
#endif

const int MAX = 1e4 + 10;

int st[K][MAX];
int mod[K];
int arr[K * K];

void add(int l, int r, int x) {
    while (l <= r && l % K) {
        st[l / K][arr[l]]--;
        arr[l] += x;
        st[l / K][arr[l]]++;
        l++;
    }
    while (l + K < r) {
        mod[l / K] += x;
        l += K;
    }
    while (l <= r) {
        st[l / K][arr[l]]--;
        arr[l] += x;
        st[l / K][arr[l]]++;
        l++;
    }
}

int get(int l, int r, int x) {
    int ans = 0;
    while (l <= r && l % K) {
        ans += (arr[l] + mod[l / K] == x);
        l++;
    }
    while (l + K < r) {
        if (x - mod[l / K] >= 0 && x - mod[l / K] < MAX) {
            ans += st[l / K][x - mod[l / K]];
        }
        l += K;
    }
    while (l <= r) {
        ans += (arr[l] + mod[l / K] == x);
        l++;
    }
    return ans;
}

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < K; i++) memset(st[i], 0, sizeof st[i]);
    memset(mod, 0, sizeof mod);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        st[i / K][arr[i]]++;
    }
    for (int i = 0; i < m; i++) {
        char q;
        cin >> q;
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--;
        if (q == '+') {
            add(l, r, x);
        } else {
            cout << (get(l, r, x) ? "YES\n" : "NO\n");
        }
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
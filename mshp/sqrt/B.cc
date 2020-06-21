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
const int K = 500;
#else
const int K = 500;
#endif

const int MAX = 1e6 + 228;

struct Query {
    int id;
    int lb;
    int rb;
    int ans;
};

int cnt[MAX];
int arr[MAX];

int lt;
int rt;
int ans = 0;

void add_left() {
    lt--;
    ans -= cnt[arr[lt]] * cnt[arr[lt]] * arr[lt];
    cnt[arr[lt]]++;
    ans += cnt[arr[lt]] * cnt[arr[lt]] * arr[lt];
}

void add_right() {
    rt++;
    ans -= cnt[arr[rt]] * cnt[arr[rt]] * arr[rt];
    cnt[arr[rt]]++;
    ans += cnt[arr[rt]] * cnt[arr[rt]] * arr[rt];
}

void rem_left() {
    ans -= cnt[arr[lt]] * cnt[arr[lt]] * arr[lt];
    cnt[arr[lt]]--;
    ans += cnt[arr[lt]] * cnt[arr[lt]] * arr[lt];
    lt++;
}

void rem_right() {
    ans -= cnt[arr[rt]] * cnt[arr[rt]] * arr[rt];
    cnt[arr[rt]]--;
    ans += cnt[arr[rt]] * cnt[arr[rt]] * arr[rt];
    rt--;
}

void run() {
    int n, t;
    cin >> n >> t;
    memset(cnt, 0, sizeof cnt);
    arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<Query> q;
    for (int i = 0; i < t; i++) {
        int l, r;
        cin >> l >> r;
        q.push_back({i, l, r, 0});
    }
    sort(all(q), [](Query a, Query b){
        a.lb /= K;
        b.lb /= K;
        return tie(a.lb, a.rb) < tie(b.lb, b.rb);
    });
    cnt[0] = 1;
    lt = rt = 0;
    for (auto &[i, l, r, res] : q) {
        while (rt < r) {
            add_right();
        }
        while (lt > l) {
            add_left();
        }
        while (rt > r) {
            rem_right();
        }
        while (lt < l) {
            rem_left();
        }
        res = ans;
    }
    sort(all(q), [](auto &a, auto &b){
        return a.id < b.id;
    });
    for (auto &el : q) {
        cout << el.ans << '\n';
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
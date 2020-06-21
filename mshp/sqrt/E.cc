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

struct Query {
    int lb;
    int rb;
    int x;
    int y;
};

void run() {
    int n, q;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    cin >> q;
    vector<Query> qs;
    vector<vector<Query>> add(n), rem(n);
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        if (a[i] >= b[i]) {
            ans[i] = 0;
        }
    }
    for (int id = 0; id < q; id++) {
        int lb, rb, x, y;
        cin >> lb >> rb >> x >> y;
        lb--;
        rb--;
        add[lb].push_back({lb, rb, x, y});
        rem[rb].push_back({lb, rb, x, y});
        qs.push_back({lb, rb, x, y});
        if ((id + 1) % K == 0 || id + 1 == q) {
            int cur = 0;
            int dt = 0;
            for (int i = 0; i < n; i++) {
                cur += dt;
                for (auto [lb, rb, x, y] : add[i]) {
                    cur += x;
                    dt += y;
                }
                if (a[i] + cur >= b[i] && ans[i] == -1) {
                    int cans = 0;
                    for (auto [lb, rb, x, y] : qs) {
                        if (lb <= i && i <= rb) {
                            a[i] += x + (i - lb) * y;
                        }
                        cans++;
                        if (a[i] >= b[i]) {
                            ans[i] = id - qs.size() + cans + 1;
                            break;
                        }
                    }
                } else {
                    a[i] += cur;
                }
                for (auto [lb, rb, x, y] : rem[i]) {
                    cur -= x;
                    dt -= y;
                    cur -= y * (rb - lb);
                }
            }
            qs.clear();
            add.assign(n, {});
            rem.assign(n, {});
        }
    }
    for (auto el : ans) {
        cout << el << ' ';
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
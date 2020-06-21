//
// Created by watemus on 26.05.2020.
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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif


void run() {
    int n, x;
    cin >> n >> x;
    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; i++) {
        d.push_back(d[i]);
    }
    vector<int> pref_days(d.size()), pref_ans(d.size());
    for (int i = 1; i < d.size(); i++) {
        pref_days[i] = pref_days[i - 1] + d[i];
        pref_ans[i] = pref_ans[i - 1] + (d[i] + 1) * d[i] / 2;
    }
    int fst = 0;
    int scd = 0;
    int ans = 0;
    while (fst < d.size()) {
        while (scd < d.size() && pref_days[scd] - pref_days[fst] < x) {
            scd++;
        }
        if (scd == d.size()) break;
        int c_days = d[scd] - (pref_days[scd] - pref_days[fst] - x);
        int cans = pref_ans[scd - 1] - pref_ans[fst] + (c_days + 1) * c_days / 2;;
        ans = max(ans, cans);
        fst++;
    }
    reverse(all(d));
    for (int i = d.size() - 2; i >= 0; i--) {
        swap(d[i], d[i + 1]);
    }
    for (int i = 1; i < d.size(); i++) {
        pref_days[i] = pref_days[i - 1] + d[i];
        pref_ans[i] = pref_ans[i - 1] + (d[i] + 1) * d[i] / 2;
    }
    fst = 0, scd = 0;
    while (fst < d.size()) {
        while (scd < d.size() && pref_days[scd] - pref_days[fst] < x) {
            scd++;
        }
        if (scd == d.size()) break;
        int c_days = (pref_days[scd] - pref_days[fst] - x);
        int cans = pref_ans[scd - 1] - pref_ans[fst] + (d[scd] + 1) * d[scd] / 2 - (c_days + 1) * c_days / 2;;
        ans = max(ans, cans);
        fst++;
    }
    reverse(all(d));
    for (int i = d.size() - 2; i >= 0; i--) {
        swap(d[i], d[i + 1]);
    }
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
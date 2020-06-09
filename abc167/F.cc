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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

inline int br2int(char ch) {
    return ch == '(' ? 1 : -1;
}



void run() {
    int n;
    cin >> n;
    vector<string> a(n);
    int all_bal = 0;
    vector<int> end_bal(n), min_bal(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int cur_bal = 0;
        for (auto ch : a[i]) {
            cur_bal += br2int(ch);
            min_bal[i] = min(min_bal[i], cur_bal);
        }
        end_bal[i] = cur_bal;
        all_bal += cur_bal;
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
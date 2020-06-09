//
// Created by watemus on 19.05.2020.
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


vector<int> pref_func(string &s) {
    vector<int> pi(s.size());
    for (int i = 1; i < s.size(); i++) {
        int val = pi[i - 1];
        while (s[val] != s[i] && val > 0) {
            val = pi[val - 1];
        }
        if (s[val] == s[i]) {
            pi[i] = val + 1;
        }
    }
    return pi;
}

vector<int> z_func(string &s) {
    vector<int> z(s.size());
    int lb, rb;
    lb = rb = 0;
    for (int i = 1; i < s.size(); i++) {
        if (i <= rb) {
            z[i] = min(z[i - lb], rb - i + 1);
        }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > rb) {
            rb = i + z[i] - 1;
            lb = i;
        }
    }
    return z;
}

void run() {
    string s;
    cin >> s;
    vector<int> pi = pref_func(s), z = z_func(s);
    int ans = 0;
    for (int i = 1; i < s.size(); i++) {
        int cans = pi[i];
        if (i + 1 < s.size()) cans += z[i + 1];
        ans = max(ans, cans);
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
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
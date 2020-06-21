//
// Created by watemus on 10.04.2020.
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

vector<int> divs;

const int MOD = 998244353;

int cnt(int a, int b) {
    a /= b;
    map<int, int> cnt;
    for (auto d : divs) {
        if (a % d == 0) {
            a /= d;
            cnt[d]++;
        }
    }
    map<vector<int>, int> dp;
    queue<vector<int>> st;
    st.push(vector<int>(cnt.size()));
    dp[st.front()] = 1;
    int last = 0;
    map<vector<int>, int> usd;
    while (st.size()) {
        auto it = cnt.begin();
        for (int i = 0; i < cnt.size(); i++) {
            auto cr = st.front();
            if (cr[i] < it->second) {
                dp[cr] += dp[st.front()];
                dp[cr] %= MOD;
                if (!usd[cr]) {
                    usd[cr] = 1;
                    st.push(cr);
                }
            }
            it++;
        }
        last = dp[st.front()];
        st.pop();
    }
    return last;
}

int len(int a, int b) {
    a /= b;
    int ans = 0;
    for (auto d : divs) {
        if (a % d == 0) {
            a/=d;
            ans++;
        }
    }
    return ans;
}

void run() {
    int D;
    cin >> D;
    int cd = D;
    for (int i = 2; i * i <= D; i++) {
        while (cd % i == 0) {
            divs.push_back(i);
            cd /= i;
        }
    }
    if (cd > 1) {
        divs.push_back(cd);
    }
    int n;
    cin >> n;
    while (n--) {
        int u, v;
        cin >> u >> v;
        int gc = gcd(u, v);
        int lc = lcm(u, v);
        if (D % lc) {
            lc = gc;
        }
        if (len(u, lc) + len(v, lc) < len(u, gc) + len(v, gc)) {

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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
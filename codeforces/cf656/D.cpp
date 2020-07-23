//
// Created by watemus on 17.07.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const ll MAXN = 131072;

ll dp0[MAXN * 2 + 228], dp1[MAXN * 2 + 228];

ll calc(ll v, ll lb, ll rb, ll k, ll cdp, string &s) {
    if (cdp == 0) {
        if (dp0[v] != -1)
            return dp0[v];
        dp0[v] = 0;
        for (ll i = lb; i < rb; i++) {
            if (s[i] - 'a' != k) dp0[v]++;
        }
        return dp0[v];
    } else {
        if (dp1[v] != -1)
            return dp1[v];
        if (rb - lb == 1) {
            dp1[v] = s[lb] - 'a' != k + 1;
            return s[lb] - 'a' != k + 1;
        }
        ll mid = (lb + rb) / 2;
        ll tl1 = calc(v * 2 + 1, lb, mid, k + 1,  0, s);
        ll tl2 = calc(v * 2 + 1, lb, mid, k + 1, 1, s);
        ll tr1 = calc(v * 2 + 2, mid, rb, k + 1, 0, s);
        ll tr2 = calc(v * 2 + 2, mid, rb, k + 1, 1, s);
        dp1[v] = min(tl1 + tr2, tl2 + tr1);
        return dp1[v];
    }
}

void run() {
    ll n;
    cin >> n;
    fill(dp0, dp0 + n + n + 10, -1);
    fill(dp1, dp1 + n + n + 10, -1);
    string s;
    cin >> s;
    cout << calc(0, 0, n, -1, 1, s) << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}



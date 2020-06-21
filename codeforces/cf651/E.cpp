//
// Created by watemus on 20.06.2020.
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

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename T1, typename T2>
using umap = unordered_map<T1, T2>;

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vec<int> a;
    int c1, c2;
    c1 = c2 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0' && t[i] == '1') {
            c1++;
            a.push_back(-1);
        } else if (s[i] == '1' && t[i] == '0') {
            c2++;
            a.push_back(1);
        }
    }
    if (c1 != c2) {
        cout << "-1\n";
        return;
    }
    int ans = 0;
    int cur = 0;
    int mx = 0, mn = 0;
    for (auto el : a) {
        cur += el;
        mx = max(cur, mx);
        mn = min(cur, mn);
        ans = max({ans, mx - cur, cur - mn});
    }
    cout << ans << '\n';
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


//
// Created by watemus on 09.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()даже умнов
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

pair<int, int> ask(int x1, int y1, int x2, int y2) {
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
    int c1, c2;
    cin >> c1 >> c2;
    return {c1, c2};
}


void run() {
    int n, m;
    cin >> n >> m;
    map<int, vec<pair<int, int>>> mp;
    for (int i = 1; i < n * m; i += 2) {
        int x1 = (i - 1) / m + 1;
        int y1 = (i - 1) % m + 1;
        int x2 = (i) / m + 1;
        int y2 = (i) % m + 1;
        auto [c1, c2] = ask(x1, y1, x2, y2);
        if (c1 == c2) continue;
        if (!mp.count(c1)) {
            mp[c1] = {{x1, y1}};
        } else {
            mp[c1].push_back({x1, y1});
        }
        if (!mp.count(c2)) {
            mp[c2] = {{x2, y2}};
        } else {
            mp[c2].push_back({x2, y2});
        }
    }
    for (auto &[x, y] : mp) {
        for (int i = 0; i + 1 < y.size(); i += 2) {
            ask(y[i].first, y[i].second, y[i + 1].first, y[i + 1].second);
        }
    }
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


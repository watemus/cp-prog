//
// Created by watemus on 13.06.2020.
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n, m;
    cin >> n >> m;
    map<int, int> cnt;
    map<pair<int, int>, int> pcnt;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        pcnt[{u, v}]++;
    }
    for (auto pr : pcnt) {
        if (pr.second > 1) {
            cnt[pr.first.first]++;
            cnt[pr.first.second]++;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (!cnt[i]) {
            cout << "1\n";
            cout << i << '\n';
            return;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            if (pcnt[{i, j}] <= 1) {
                cout << "2\n";
                cout << i << ' ' << j << '\n';
                return;
            }
        }
    }
    if (m <= 2) {
        cout << "-1\n";
    } else {
        cout << "3\n";
        cout << "1 2 3\n";
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


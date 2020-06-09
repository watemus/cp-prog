//
// Created by watemus on 05.06.2020.
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
    int n;
    cin >> n;
    vec<pair<int, int>> a(n);
    for (auto &[x, y] : a) cin >> x >> y;
    sort(all(a));
    if (n % 2) {
        int mx1 = a[n/2].first;
        sort(all(a), [](auto a, auto b){
            return a.second < b.second;
        });
        int mx2 = a[n/2].second;
        cout << mx2 - mx1 + 1 << '\n';
    } else {
        int mx11 = a[n/2-1].first;
        int mx12 = a[n/2].first;
        sort(all(a), [](auto a, auto b){
            return a.second < b.second;
        });
        int mx21 = a[n/2-1].second;
        int mx22 = a[n/2].second;
        cout << mx22 + mx21 - mx11 - mx12 + 1 << '\n';
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


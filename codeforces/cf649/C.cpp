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
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n;
    cin >> n;
    set<int> cr;
    for (int i = 0; i < n * 3; i++) {
        cr.insert(i);
    }
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > i + 1) {
            cout << "-1\n";
            return;
        }
        if (cr.count(a[i])) cr.erase(a[i]);
    }
    vec<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = *cr.begin();
        cr.erase(b[i]);
        if (i == n - 1 || (i < n - 1 && a[i] != a[i + 1])) {
            cr.insert(a[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << b[i] << ' ';
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


//
// Created by watemus on 12.06.2020.
//
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

bool eq(pair<int, int> &a, vector<int>  &b, int pb, int pa) {
    if (a.first == -2)
        return false;
    if (b[pb] == -2) return false;
    bool rs1 = (a.first == -1 || b[pb - (pa - a.first)] > b[pb]);
    bool rs2 = (a.second == -1 || b[pb - (pa - a.second)] < b[pb]);
    return rs1 && rs2;
}

void run() {
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> ast;
    vec<int> pa(n);
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;
        el--;
        pa[el] = i + 1;
    }
    vec<pair<int, int>> a(n + 1 + m);
    vec<int> b(n + m + 1);
    for (int i = 0; i < n; i++) {
        int el = pa[i];
        b[i] = el;
        auto it = ast.lower_bound({el, 0});
        if (it == ast.end()) {
            a[i].first = -1;
        } else {
            a[i].first = it->second;
        }
        if (it == ast.begin()) {
            a[i].second = -1;
        } else {
            a[i].second = prev(it)->second;
        }
        ast.emplace(el, i);
    }
    pa.clear();
    pa.shrink_to_fit();
    ast.clear();
    for (int i = 0; i < m; i++) {
        int el;
        cin >> el;
        b[i + 1 + n] = el;
    }
    a[n] = {-2, -2};
    b[n] = -2;
    vec<int> ans, pi(a.size());
    for (int i = 1; i < a.size(); i++) {
        int cr = pi[i - 1];
        while (cr > 0 && !eq(a[cr], b, i, cr)) {
            cr = pi[cr - 1];
        }
        if (eq(a[cr], b, i, cr)) {
            pi[i] = cr + 1;
        }
        if (pi[i] == n)
            ans.push_back(i - 2 * n + 1);
    }
    cout << ans.size() << '\n';
    for (auto el : ans) {
        cout << el << ' ';
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



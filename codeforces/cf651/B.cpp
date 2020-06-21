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
    vec<pair<int, int>> odd, even;
    for (int i = 0; i < 2 * n; i++) {
        int el;
        cin >> el;
        if (el % 2) {
            odd.emplace_back(el, i);
        } else {
            even.emplace_back(el, i);
        }
    }
    if (odd.size() % 2 && even.size() % 2) {
        odd.pop_back();
        even.pop_back();
    } 
    vec<pair<int, int>> ans;
    while (odd.size() >= 2 && ans.size() < n - 1) {
        pair<int, int> pr;
        pr.first = odd.back().second;
        odd.pop_back();
        pr.second = odd.back().second;
        odd.pop_back();
        ans.push_back(pr);
    }
    while (even.size() >= 2 && ans.size() < n - 1) {
        pair<int, int> pr;
        pr.first = even.back().second;
        even.pop_back();
        pr.second = even.back().second;
        even.pop_back();
        ans.push_back(pr);
    }
    for (auto [x, y] : ans) {
        cout << x + 1 << ' ' << y + 1 << '\n';
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}



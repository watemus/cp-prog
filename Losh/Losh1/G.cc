//
// Created by watemus on 08.06.2020.
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
const int BLOCK = 500;
#else
const int BLOCK = 500;
#endif



vec<int> a;
vec<vec<int>> sorted, ordered;
vec<int> dt;

void run() {
    int n, q;
    cin >> n >> q;
    a.resize(n);
    sorted.resize(n);
    ordered.resize(n);
    dt.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorted[i / BLOCK].push_back(a[i]);
        ordered[i / BLOCK].push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        sort(all(sorted[i]));
    }
    vec<int> vans;
    while (q--) {
        int t, l, r, x;
        cin >> t >> l >> r >> x;
        l--; r--;
        if (t == 1) {
            int ans = 0;
            while (l <= r && l % BLOCK != 0) {
                if (ordered[l / BLOCK][l % BLOCK] + dt[l / BLOCK] < x) ans++;
                l++;
            }
            while (l + BLOCK <= r) {
                ans += lower_bound(all(sorted[l / BLOCK]), x - dt[l / BLOCK]) - sorted[l / BLOCK].begin();
                l += BLOCK;
            }
            while (l <= r) {
                if (ordered[l / BLOCK][l % BLOCK] + dt[l / BLOCK] < x) ans++;
                l++;
            }
            vans.push_back(ans);
        } else {
            int sl = l;
            int sr = r;
            while (l <= r && l % BLOCK != 0) {
                ordered[l / BLOCK][l % BLOCK] += x;
                l++;
            }
            while (l + BLOCK <= r) {
                dt[l / BLOCK] += x;
                l += BLOCK;
            }
            while (l <= r) {
                ordered[l / BLOCK][l % BLOCK] += x;
                l++;
            }
            sorted[sl / BLOCK] = ordered[sl / BLOCK];
            sorted[sr / BLOCK] = ordered[sr / BLOCK];
            sort(all(sorted[sl / BLOCK]));
            sort(all(sorted[sr / BLOCK]));
        }
    }
    for (int i = 0; i < vans.size(); i++) {
        cout << vans[i] << "\n "[i==vans.size()-1];
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


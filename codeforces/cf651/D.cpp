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
    int n, k;
    cin >> n >> k;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int lb = 0;
    int rb = INFI;
    while (lb + 1 < rb) {
        int mid = (lb + rb) / 2;
        vec<int> dp1(n + 1), dp0(n + 1);
        for (int i = 1; i <= n; i++) {
            if (a[i - 1] <= mid) {
                dp1[i] = dp0[i - 1] + 1;
            } else {
                dp1[i] = 0;
            }
            dp0[i] = max(dp0[i - 1], dp1[i - 1] + 1);
        }
        if (max(dp0[n], dp1[n]) >= k) {
            rb = mid;
        } else {
            lb = mid;
        }
    }
    cout << rb << '\n';
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


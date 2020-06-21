//
// Created by watemus on 08.06.2020.
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

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

inline pair<int, int> check(vec<int> &a, int k, int mid) {
    gp_hash_table<int, int> cnt;
    for (int i = 0; i < k; i++) {
        cnt[a[i]]++;
    }
    if (cnt.size() >= mid) return {1, k};
    for (int i = k; i < a.size(); i++) {
        cnt[a[i-k]]--;
        if (cnt[a[i-k]] == 0)
            cnt.erase(a[i-k]);
        cnt[a[i]]++;
        if (cnt.size() >= mid) return {i - k + 2, i + 1};
    }
    return {-1, -1};//dslk
}

void run() {
    int n, k;
    cin >> n >> k;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int lb = k - 1;
    int rb = n + 1;
    int al, ar;
    while (lb + 1 < rb) {
        int mid = (lb + rb) / 2;
        auto cc= check(a, mid, k);
        int cl = cc.first;
        int cr = cc.second;
        if (cl != -1) {
            rb = mid;
            al = cl, ar = cr;
        } else {
            lb = mid;
        }
    }
    cout << al << " " << ar << '\n';
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


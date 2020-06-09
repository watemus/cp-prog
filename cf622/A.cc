//
// Created by watemus on 06.06.2020.
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
    int sa, sb, sc;
    cin >> sa >> sb >> sc;
    int ans = 0;
    vector<int> masks(7);
    for (int i = 0; i < 7; i++) masks[i] = i + 1;
    do {
        int a = sa, b = sb, c= sc;
        int cans = 0;
        for (auto mask : masks) {
            int ta = a, tb = b, tc = c;
            if ((1 << 0) & mask) ta--;
            if ((1 << 1) & mask) tb--;
            if ((1 << 2) & mask) tc--;
            if (ta >= 0 && tb >= 0 && tc >= 0) {
                a = ta, b = tb, c = tc;
                cans++;
            }
            ans = max(cans, ans);
        }
    } while (next_permutation(all(masks)));
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


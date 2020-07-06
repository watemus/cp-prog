//
// Created by watemus on 28.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n;
    cin >> n;
    int cnt2 = 0, cnt3 = 0;
    while (n % 2 == 0) {
        n /= 2;
        cnt2++;
    }
    while (n % 3 == 0) {
        n /= 3;
        cnt3++;
    }
    if (n > 1 || cnt2 > cnt3) {
        cout <<  "-1\n";
    } else {
        cout << cnt3 - cnt2 + cnt3 << '\n';
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
    cout << std::fixed << std::setprecision(20);
    int t = 1;
   cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


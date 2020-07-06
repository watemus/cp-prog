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
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vec<int> ans;
    auto modify = [&](int i) {
        ans.push_back(i + 1);
        vec<int> cr = {a[i], a[i + 1], a[i + 2]};
        a[i] = cr[2];
        a[i + 1] = cr[0];
        a[i + 2] = cr[1];
    };
    for (int rb = n; rb > 3; rb--) {
        int m = 0;
        for (int i = 1; i < rb; i++) {
            if (a[i] >= a[m]) m = i;
        }
        for (int i = m; i < rb - 1; i++) {
            modify(max(0, min(i - 1 , rb - 3))
            );
        }
    }
    int iters = 0;
    while ((a[0] > a[1] || a[1] > a[2] || a[0] > a[2]) && iters < 5) {
        iters++;
        modify(0);
    }
    if (a[0] > a[1] || a[1] > a[2] || a[0] > a[2]) {
        cout << "-1\n";
    } else {
        cout << ans.size() << '\n';
        for (auto el : ans) {
            cout << el << ' ';
        }
        cout << '\n';
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


//
// Created by watemus on 16.06.2020.
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
    string s;
    cin >> s;
    int m;
    cin >> m;
    vec<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];
    vec<int> cnt(26);
    for (auto ch : s) cnt[ch - 'a']++;
    vec<int> z;
    for (int i = 0; i < m; i++) {
        if (b[i] == 0) z.push_back(i);
    }
    string ans(m, '*');
    for (char ch = 'z'; ch >= 'a'; ch--) {
        if (cnt[ch - 'a'] >= z.size()) {
            for (auto el : z) {
                ans[el] = ch;
            }
            for (int i = 0; i < m; i++) {
                for (int j : z) {
                    if (i == j) {
                        b[i] = -1;
                        break;
                    }
                    b[i] -= abs(i - j);
                }
            }
            z.clear();
            for (int i = 0; i < m; i++) {
                if (b[i] == 0) {
                    z.push_back(i);
                }
            }
        }
    }
    cout << ans << "\n";
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


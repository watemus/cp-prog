//
// Created by watemus on 11.06.2020.
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

const int MOD1 = 1e9 + 7;
const int MOD2 = 998344353;

void run() {
    int cnt = 2.9e6;
    vec<int> fib1(cnt), fib2(cnt);
    uset<int> st;
    st.reserve(cnt);
    fib1[0] = fib1[1] = fib2[0] = fib2[1] = 1;
    for (int i = 2; i < cnt; i++) {
        fib1[i] = (fib1[i - 1] + fib1[i - 2]) % MOD1;
        fib2[i] = (fib2[i - 1] + fib2[i - 2]) % MOD2;
    }
    for (int i = 0; i < cnt; i++) {
        st.insert(fib1[i] * fib2[i]);
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int a1 = 0, a2 = 0;
        for (auto ch : s) {
            a1 = (a1 * 10 + ch - '0') % MOD1;
            a2 = (a2 * 10 + ch - '0') % MOD2;
        }
        if (st.count(a1 * a2)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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


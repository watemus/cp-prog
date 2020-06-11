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

const int MAX = 1e7 + 10;

int t[MAX];

void run() {
    memset(t, -1, sizeof t);
    for (int i = 2; i < MAX; i++) {
        if (t[i] == -1) {
            t[i] = i;
            for (int j = i; j < MAX; j += i) {
                t[j] = i;
            }
        }
    }
    int n;
    cin >> n;
    vec<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;
        int d1 = t[el];
        int d2 = t[el / d1];
        if (gcd(d1 + d2, el) == 1 && d2 > 1) {
            a[i] = d1;
            b[i] = d2;
        } else {
            a[i] = b[i] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    for (int i = 0 ; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << '\n';
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


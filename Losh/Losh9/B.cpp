//
// Created by watemus on 17.06.2020.
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
    int a, b, c, n;
    cin >> c >> b >> a >> n;
    vec<int> v1, v2, v3;
    vec<int> coords;
    for (int i = 0; i < n; i++) {
        int y, s;
        cin >> y >> s;
        if (y == 1994) v3.push_back(s);
        if (y == 1995) v2.push_back(s);
        if (y == 1996) v1.push_back(s);
        coords.push_back(s);
    }
    sort(rall(v1)), sort(rall(v2)), sort(rall(v3));
    if( v1.size() == 0 || v2.size() == 0 || v3.size() == 0) {
        cout << "-1\n";
        return;
    }
    int p1 = 0, p2 = 0, p3 = 0;
    for (; p2 < v2.size() && p1 < v1.size() && v2[p2] > v3[p1]; p2++);
    for (; p1 < v1.size() && p2 < v2.size() && v1[p1] > v2[p2]; p1++);
    if (p2 == v2.size() || p1 == v1.size() || p3 == v3.size() || p1 + p2 + p3 + 3 > a + b + c) {
        cout <<"-1\n";
        return;
    }
    while (p1 + p2 + p3 + 3 < a + b + c) {
        if (p1 < int(v1.size()) - 1 && p1 < a - 1) {
            p1++;
        } else if (p2 < int(v2.size()) - 1 && p2 < b - 1 && v2[p2 + 1] > v1[p1]) {
            p2++;
        } else if (p3 < int(v3.size()) - 1 && p3 < c - 1 && v3[p3 + 1] > v2[p2]) {
            p3++;
        } else if (p1 < int(v1.size()) - 1 && p2 < b - 1) {
            p1++;
        } else if (p2 < int(v2.size()) - 1 && p3 < c - 1 && v2[p2 + 1] > v1[p1]) {
            p2++;
        } else if (p3 < int(v3.size()) - 1 && v3[p3 + 1] > v2[p2]) {
            p3++;
        } else if (p2 < int(v2.size()) - 1 && v2[p2 + 1] > v1[p1]) {
            p2++;
        } else if (p1 < int(v1.size()) - 1) {
            p1++;
        } else {
            cout << "-1\n";
            return;
        }
    }
    cout << abs(a - (p1 + 1)) + abs(b - (p2 + 1)) + abs(c - (p3 + 1));
    cout << " " << p3 + 1 << " " << p2 + 1 << ' ' << p1 + 1 << '\n';
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


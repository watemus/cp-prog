//
// Created by watemus on 19.06.2020.
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

struct Pt {
    int x, y;
};

int operator*(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}

Pt operator+(Pt a, Pt b) {
    return {a.x + b.x, a.y + b.y};
}

Pt operator-(Pt a, Pt b) {
    return {a.x - b.x, a.y - b.y};
}

int sign(int a) {
    if (a == 0) return 0;
    return a / abs(a);
}

void run() {
    int n;
    cin >> n;
    vec<Pt> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < n; i++) {
        a.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        a.push_back(a[i]);
    }
    int t;
    cin >> t;
    while (t--) {
        int j = 1;
        int ans = 0;
        Pt p;
        cin >> p.x >> p.y;
        bool in = true;
        for (int i = 0; i < n; i++) {
            j = max(j, i + 1);
            ans += (j - i) * (j - i - 1) / 2;
            in &= (sign((a[i + 1] - a[i]) * (p - a[i])) == sign((a[i + 2] - a[i + 1]) * (p - a[i + 1])));
            while (true) {
                auto v1 = a[j] - a[i];
                auto v2 = a[j + 1] - a[i];
                auto vp = p - a[i];
                if (sign(v1 * vp) == sign(v2 * vp)) {
                    j++;
                    ans += j - i - 1;
                }
                else
                    break;
            }
        }
        if (in)
            cout << n * (n - 1) * (n - 2) / 6 - ans << '\n';
        else
            cout << "0\n";
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


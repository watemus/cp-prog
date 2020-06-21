//
// Created by watemus on 15.06.2020.
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

const ld EPS = 1e-9;

struct Pt {
    ld x, y;
};

struct Circle {
    Pt c;
    ld r;
};



ld dist(Pt a, Pt b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool inter(Circle &a, Circle &b) {
    return dist(a.c, b.c) < a.r + b.r;
}

void upd_r(Circle &a, Circle &b) {
    ld lb = 0;
    ld rb = a.r;
    for (int iter = 0; iter < 40; iter++) {
        ld mid = (lb + rb) / 2;
        a.r = mid;
        a.c.y = mid;
        if (inter(a, b)) {
            rb = mid;
        }
        if (rb != mid) {
            lb = mid;
        }
    }
}//

void run() {
    int n;
    cin >> n;
    vec<Circle> a(n);
    vec<Circle> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i].c.x >> a[i].r;
        a[i].c.y = a[i].r;
        while (st.size()) {
            upd_r(a[i], st.back());
            if (a[i].r >= st.back().r) {
                st.pop_back();
            } else {
                break;
            }
        }
        st.push_back(a[i]);
    }
    for (int i = 0; i < n; i++) {
        cout << a[i].r << '\n';
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


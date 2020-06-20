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
    ld x, y, z;
};

Pt operator+(Pt a, Pt b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Pt operator-(Pt a, Pt b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

ld dist(Pt a, Pt b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

Pt setlen(Pt p, ld len) {
    ld clen = dist({0, 0, 0}, p);
    p.x /= clen;
    p.y /= clen;
    p.z /= clen;
    p.x *= len;
    p.y *= len;
    p.z *= len;
    return p;
}

const ld EPS = 1e-13;

void run() {
    int n;
    cin >> n;
    vec<Pt> way(n + 1);
    for (auto &p : way) {
        cin >> p.x >> p.y >> p.z;
    }
    ld vs, vt;
    cin >> vt >> vs;
    Pt st;
    cin >> st.x >> st.y >> st.z;
    ld L = 0;
    ld R = INFL;
    ld asdist = 0;
    for (int i = 1; i < n + 1; i++) {
        asdist += dist(way[i], way[i - 1]);
    }
    bool checked = false;
    Pt lst;
    for (int iter = 0; iter < 1000; iter++) {
        ld mid = (L + R) / 2;
        ld sdist = vs * mid;
        if (sdist - asdist > EPS) {
            R = mid;
            continue;
        }
        int cr = 0;
        for (int i = 1; i < n + 1; i++) {
            if (sdist - dist(way[i - 1], way[i]) > EPS) {
                cr = i;
                sdist -= dist(way[i - 1], way[i]);
            } else {
                break;
            }
        }
        if (cr == n) {
            if (dist(st, way[cr]) / vt <= mid + EPS) {
                R = mid;
                checked = true;
                lst = way[cr];
            } else {
                L = mid;
            }
        } else {
            Pt vc = way[cr + 1] - way[cr];
            vc = setlen(vc, sdist);
            if (dist(st, way[cr] + vc) / vt <= mid + EPS) {
                R = mid;
                checked = true;
                lst = way[cr] + vc;
            } else {
                L = mid;
            }
        }
    }
    if (checked) {
        cout << "YES\n";
        cout << L << '\n';
        cout << lst.x << ' ' << lst.y << ' ' << lst.z << '\n';
    } else {
        cout << "NO\n";
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


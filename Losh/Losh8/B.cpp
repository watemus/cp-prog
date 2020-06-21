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

constexpr ld EPS = 1e-10;

struct Pt {
    ld x, y;
    Pt(ld x, ld y) :x(x), y(y) {}
    Pt() : Pt(0, 0) {}
    Pt(Pt a, Pt b) : Pt(b.x - a.x, b.y - a.y) {}
    ld len() {
        return sqrt(x * x + y * y);
    }
};

Pt operator+(Pt a, Pt b) {
    return Pt(a.x + b.x, a.y + b.y);
}

Pt operator-(Pt a, Pt b) {
    return Pt(a.x - b.x, a.y - b.y);
}

ld dist(Pt &a, Pt &b) {
    return (a - b).len();
}

struct Line {
    ld a, b, c;
    Line(ld a, ld b, ld c) : a(a), b(b), c(c) {}
    Line() : Line(1, 1, 1) {}
    Line(Pt p, Pt q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
    }
};

Pt intersect(Line a, Line b) {
    ld rem = a.a * b.b - a.b * b.a;
    Pt res;
    res.x = -((a.c * b.b - a.b * b.c) / rem);
    res.y = -((a.a * b.c - a.c * b.a) / rem);
    return res;
}

ld dist(Line a, Pt p) {
    return fabs(a.a * p.x + a.b * p.y + a.c) / sqrt(a.a * a.a + a.b * a.b);
}

void run() {
    int n, m;
    cin >> n >> m;
    vec<Line> metro(n), hel(m);
    for (int i = 0; i < n; i++) {
        ld a, b, c;
        cin >> a >> b >> c;
        metro[i] = Line(a, b, c);
    }
    for (int i = 0; i < m; i++) {
        ld a, b, c;
        cin >> a >> b >> c;
        hel[i] = Line(a, b, c);
    }
    for (int i = 0; i < m; i++) {
        ld ans = INFI;
        vec<pair<Pt, Line>> vc;
        for (int j = 0; j < n; j++) {
            vc.emplace_back(intersect(hel[i], metro[j]), metro[j]);
        }
        sort(all(vc), [](auto a, auto b) {
            if (fabs(a.first.x - b.first.x) < EPS) {
                return a.first.y < b.first.y;
            }
            return a.first.x < b.first.x;
        });
        for (int j = 0; j < vc.size() - 1; j++) {
            ans = min(ans, dist(hel[i], intersect(vc[j].second, vc[j + 1].second)));
        }
        cout << ans << '\n';
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


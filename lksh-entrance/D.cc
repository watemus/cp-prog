//
// Created by watemus on 18.05.2020.
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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld EPS = 1e-9;

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

struct Vec {
    ld x, y;
    Vec(ld x, ld y) : x(x), y(y) {}
    Vec() : Vec(0, 0) {}
    Vec(Vec a, Vec b) : x(b.x- a.x), y(b.y - a.y) {}
    ld len() {
        return sqrt(x * x + y * y);
    }
};

Vec operator+(Vec a, Vec b) {
    return Vec(a.x + b.x, a.y + b.y);
}

Vec operator-(Vec a) {
    return Vec(-a.x, -a.y);
}

Vec operator-(Vec a, Vec b) {
    return Vec(a.x - b.x, a.y - b.y);
}

Vec operator*(Vec a, ld k) {
    return Vec(a.x * k, a.y * k);
}

Vec operator/(Vec a, ld k) {
    return Vec(a.x / k, a.y / k);
}

ld operator*(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}

ld operator%(Vec a, Vec b) {
    return a.x * b.x + a.y + b.y;
}

ld dist(Vec a, Vec b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Vec rotate(Vec oth) {
    return Vec(-oth.y, oth.x);
}

bool operator==(Vec a, Vec b) {
    return fabs(a.x - b.x) <= EPS && fabs(a.y - b.y) <= EPS;
}

struct Line {
    ld a;
    ld b;
    ld c;
    Line(ld a, ld b, ld c) : a(a), b(b), c(c) {}
    Line() : Line(0, 0, 0) {}
    Line(Vec p, Vec q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -(a * p.x) - b * p.y;
    }
};

bool parallel(Line p, Line q) {
    return fabs(p.a * q.b - p.b * q.b) <= EPS;
}

Vec intersect(Line p, Line q) {
    ld x = -((p.c * q.b - q.c * p.b)/(p.a * q.b - q.a * p.b));
    ld y = -((p.a * q.c - q.a * p.c)/(p.a * q.b - q.a * p.b));
    return Vec(x, y);
}

struct Circle {
    Vec p;
    ld r;
};

bool check(Circle target, vector<Circle> &circles) {
    for (auto &circle : circles) {
        ld _dist = dist(circle.p, target.p) + circle.r;
        if (target.r - _dist > -EPS) continue;
        return false;
    }
    return true;
}

ld get_radius(Vec c, vector<Circle> &circles) {
    ld ans = 0;
    for (auto [O, R] : circles) {
        ans = max(ans, dist(c, O) + R);
    }
    return ans;
}

ld ternary_y(ld x, vector<Circle> &circles) {
    ld lb = -10000;
    ld rb = +10000;
    for (int iter = 0; iter < 100; iter++) {
        ld y1 = lb + (rb - lb) / 3;
        ld y2 = lb + (rb - lb) / 3 * 2;
        ld r1 = get_radius(Vec(x, y1), circles);
        ld r2 = get_radius(Vec(x, y2), circles);
        if (r1 < r2) rb = y2;
        else lb = y1;
    }
    return get_radius(Vec(x, lb), circles);
}

ld ternary_x(vector<Circle> &circles) {
    ld lb = -10000;
    ld rb = +10000;
    for (int iter = 0; iter < 100; iter++) {
        ld x1 = lb + (rb - lb) / 3;
        ld x2 = lb + (rb - lb) / 3 * 2;
        ld r1 = ternary_y(x1, circles);
        ld r2 = ternary_y(x2, circles);
        if (r1 < r2) rb = x2;
        else lb = x1;
    }
    return ternary_y(lb, circles);
}



void run() {
    int n;
    cin >> n;
    vector<Circle> circles(n);
    for (auto &circle : circles) {
        cin >> circle.p.x >> circle.p.y >> circle.r;
    }
    cout << fixed << setprecision(228);
    cout << ternary_x(circles) << '\n';
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}
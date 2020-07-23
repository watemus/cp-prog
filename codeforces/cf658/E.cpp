//
// Created by watemus on 21.07.2020.
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

#define int ll

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

constexpr long double EPS = 1e-5;

using FET = ld;

struct FloatEps {
  FET val;
  explicit FloatEps(FET val) : val(val) {}
  FloatEps() : val(0) {}
  operator FET() const {
    return val;
  }
  inline FloatEps& operator+=(FloatEps oth) {
    val += oth.val;
    return *this;
  }
  inline FloatEps& operator-=(FloatEps oth) {
    val -= oth.val;
    return *this;
  }
  inline FloatEps& operator*=(FloatEps oth) {
    val *= oth.val;
    return *this;
  }
  inline FloatEps &operator/=(FloatEps oth) {
    val /= oth.val;
    return *this;
  }
};

inline FloatEps operator+(FloatEps a, FloatEps b) {
  return a += b;
}


inline FloatEps operator-(FloatEps a, FloatEps b) {
  return a -= b;
}


inline FloatEps operator*(FloatEps a, FloatEps b) {
  return a *= b;
}


inline FloatEps operator/(FloatEps a, FloatEps b) {
  return a /= b;
}

inline FloatEps operator-(FloatEps a) {
  return FloatEps(-a.val);
}

inline bool operator==(FloatEps a, FloatEps b) {
  return fabs(a.val - b.val) <= EPS;
}


inline bool operator!=(FloatEps a, FloatEps b) {
  return fabs(a.val - b.val) > EPS;
}


inline bool operator<(FloatEps a, FloatEps b) {
  return b.val - a.val > EPS;
}


inline bool operator>(FloatEps a, FloatEps b) {
  return a.val - b.val > EPS;
}


inline bool operator<=(FloatEps a, FloatEps b) {
  return a < b || a == b;
}


inline bool operator>=(FloatEps a, FloatEps b) {
  return a > b || a == b;
}

using ldp = FloatEps;

#ifdef LOCAL
#else
#endif

struct Pt {
  ldp x, y;
  Pt(ldp xx, ldp yy)
  : x(xx), y(yy)
  {}
  Pt() : Pt(ldp(0), ldp(0)) {}
};

Pt operator+(Pt a, Pt b) {
  return Pt(a.x + b.x, a.y - b.y);
}

Pt operator-(Pt a, Pt b) {
  return Pt(a.x - b.x, a.y - b.y);
}

ldp operator*(Pt a, Pt b) {
  return a.x * b.y - a.y * b.x;
}

ldp operator%(Pt a, Pt b) {
  return a.x * b.x + a.y * b.y;
}

struct Seg {
  Pt p, q;
  Seg(Pt p, Pt q) : p(p), q(q) {}
  Seg() : Seg(Pt(), Pt()) {}
};

struct Line {
  ldp A, B, C;
  Line(ldp a, ldp b, ldp c)
  : A(a), B(b), C(c) {}
  Line() : Line(ldp(0), ldp(0), ldp(0)) {}
  explicit Line(Seg s) {
    A = s.p.y - s.q.y;
    B = s.q.x - s.p.x;
    C = -(A * s.p.x) - B * s.p.y;
  }
  pair<ldp, ldp> norm() {
    if (B == ldp(0)) {
      return {ldp(0), ldp(0)};
    }
    return {-(A/B), -(C/B)};
  }
};

Pt inter(Line ln1, Line ln2) {
  ldp x = -(ln1.C * ln2.B - ln2.C * ln1.B) / (ln1.A * ln2.B - ln2.A * ln1.B);
  ldp y = -(ln1.A * ln2.C - ln2.A * ln1.C) / (ln1.A * ln2.B - ln2.A * ln1.B);
  return Pt(x, y);
}

bool half_pon(Seg s, Pt p) {
  return (s.p % (s.q - p)) >= ldp(0);
}

bool pon(Seg s, Pt p) {
  return half_pon(s, p) && half_pon(Seg(s.q, s.p), p);
}

bool is_inter(Line ln, Seg s) {
  Pt p = inter(ln, Line(s));
  return pon(s, p);
}

struct Event {
  // Vertical line
  bool vert;
  int x;
  int id;
  // Segment
  ldp x1, x2;
  ldp xs, xf;
  ldp k;
  ldp b;
  ldp coef;
  bool end;
  ldp integral(ldp xx) {
    return k * xx * xx / ldp(2) + b * xx;
  }
  ldp calc_area() {
    ldp xx1 = integral(x1);
    ldp xx2 = integral(x2);
    xx1 -= xx2;
    return xx1 * coef;
  }
  Event(bool vert) : vert(vert), end(false) {}
};

const int MAXN = 1e5 + 10;

void run() {
  int n, q;
  cin >> n >> q;
  vec<Pt> poly(n);
  vector<int> ys;
  int mny = INFI, mxy = -INFI;
  int mnx = INFI;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    mny = min(y, mny);
    mxy = max(y, mxy);
    mnx = min(x, mnx);
    ys.push_back(y);
    poly[i] = Pt(ldp(x), ldp(y));
  }
  for (int i = 0; i < n; i++) {
    poly[i].x.val -= mnx;
    poly[i].y.val -= mny;
    ys[i] -= mny;
  }
  sort(ALL(ys));
  ys.resize(unique(ALL(ys)) - ys.begin());
  vec<Pt> left, right;
  // Making left and right hulls
  {
    bool found = false;
    vec<Pt> *cur = &right;
    int i = 0;
    while (left.size() + right.size() <= n) {
      if (int(poly[i].y.val) == 0) {
        found = true;
      }
      if (found) {
        cur->push_back(poly[i]);
      }
      if (found && int(poly[i].y.val) == mxy - mny) {
        cur = &left;
        cur->push_back(poly[i]);
      }
      i++;
      i %= n;
    }
    left.push_back(right.front());
    if ((right[right.size() - 2] - right[right.size() - 1]) * (left[0] - left[1]) < ldp(0)) {
      swap(left, right);
      reverse(ALL(left));
      reverse(ALL(right));
    }
    reverse(ALL(left));
  }
  // Dividing segments
  auto divide = [&](vec<Pt> &p) {
    vec<Pt> new_p;
    new_p.push_back(p[0]);
    for (int i = 0; i < p.size() - 1; i++) {
      int beg_y = p[i].y.val;
      int nd_y = p[i + 1].y.val;
      for (auto it = upper_bound(ALL(ys), beg_y); it != ys.end() && *it < nd_y; it++) {
        Line ln(Seg(Pt(ldp(0), ldp(*it)), Pt(ldp(1), ldp(*it))));
        new_p.push_back(inter(ln, Line(Seg(p[i], p[i + 1]))));
      }
      new_p.push_back(p[i + 1]);
    }
    return new_p;
  };
  left = divide(left);
  right = divide(right);
  // Making midline
  assert(left.size() == right.size());
  vec<Pt> midline;
  for (int i = 0; i < left.size(); i++) {
    midline.emplace_back((left[i].x + right[i].x) / ldp(2), left[i].y);
  }
  // Making 2 polygons
  vec<Pt> minus = midline, plus = right;
  for (int i = midline.size() - 2; i >= 1; i--) {
    minus.push_back(left[i]);
    plus.push_back(midline[i]);
  }
  // Making sweep line
  vec<Event> sweep_line;
  auto add_vert = [&](int x, int id) {
    sweep_line.push_back(Event(true));
    sweep_line.back().x = x;
    sweep_line.back().id = id;
  };
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    x -= mnx;
    add_vert(x, i);
  }
  auto add_seg = [&](Seg s, ldp coef) {
    auto [k, b] = Line(s).norm();
    sweep_line.push_back(Event(false));
    sweep_line.back().x1 = s.p.x;
    sweep_line.back().x2 = s.q.x;
    sweep_line.back().xs = min(s.p.x, s.q.x);
    sweep_line.back().xf = max(s.p.x, s.q.x);
    sweep_line.back().k = k;
    sweep_line.back().b = b;
    sweep_line.back().coef = coef;
    sweep_line.back().end = false;
    sweep_line.push_back(Event(false));
    sweep_line.back().x1 = s.p.x;
    sweep_line.back().x2 = s.q.x;
    sweep_line.back().xs = min(s.p.x, s.q.x);
    sweep_line.back().xf = max(s.p.x, s.q.x);
    sweep_line.back().k = k;
    sweep_line.back().b = b;
    sweep_line.back().coef = coef;
    sweep_line.back().end = true;
  };
  ldp total_area = ldp(0);
  for (int i = 0; i < minus.size() - 1; i++) {
    add_seg(Seg(minus[i], minus[i + 1]), ldp(-1));
    total_area += minus[i] * minus[i + 1];
  }
  total_area += minus.back() * minus.front();
  add_seg(Seg(minus.back(), minus.front()), ldp(-1));
  for (int i = 0; i < plus.size() - 1; i++) {
    add_seg(Seg(plus[i], plus[i + 1]), ldp(1));
    total_area += plus[i] * plus[i + 1];
  }
  total_area += plus.back() * plus.front();
  add_seg(Seg(plus.back(), plus.front()), ldp(1));
  total_area /= ldp(2);
  vec<ldp> ans(q);
  ldp area = total_area;
  ldp sum_k, sum_b;
  ldp left_rm;
  sort(ALL(sweep_line), [](const auto &ev1, const auto &ev2) {
    ldp x1 = (ev1.vert ? ldp(ev1.x) : (!ev1.end ? ev1.xs : ev1.xf));
    ldp x2 = (ev2.vert ? ldp(ev2.x) : (!ev2.end ? ev2.xs : ev2.xf));
    if (ev1.vert && ev2.vert) {
      return ev1.x < ev2.x;
    }
    if (ev1.vert && x1 == x2) {
      return false;
    }
    if (ev2.vert && x1 == x2) {
      return true;
    }
    return x1 < x2;
  });
  for (auto ev : sweep_line) {
    if (ev.vert) {
      ans[ev.id] = area;
      ans[ev.id] += (sum_k * ldp(ev.x * ev.x)) / ldp(2) + sum_b * ldp(ev.x);
      ans[ev.id] -= left_rm;
    } else {
      if (!ev.end) {
        if (ev.x1 > ev.x2) {
          sum_k += ev.k * ev.coef;
          sum_b += ev.b * ev.coef;
          left_rm += (ev.k * ldp(ev.xs * ev.xs)) / ldp(2) + ev.b * ldp(ev.xs) * ev.coef;
        } else {
          sum_k -= ev.k * ev.coef;
          sum_b -= ev.b * ev.coef;
          left_rm -= (ev.k * ldp(ev.xs * ev.xs)) / ldp(2) + ev.b * ldp(ev.xs) * ev.coef;
        }
      } else {
        area += ev.calc_area();
        if (ev.x1 > ev.x2) {
          sum_k -= ev.k * ev.coef;
          sum_b -= ev.b * ev.coef;
          left_rm -= (ev.k * ldp(ev.xs * ev.xs)) / ldp(2) + ev.b * ldp(ev.xs) * ev.coef;
        } else {
          sum_k += ev.k * ev.coef;
          sum_b += ev.b * ev.coef;
          left_rm += (ev.k * ldp(ev.xs * ev.xs)) / ldp(2) + ev.b * ldp(ev.xs) * ev.coef;
        }
      }
    }
  }
  for (auto el : ans) {
    cout << el.val << '\n';
  }
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  //cin >> t;
  cout << fixed << setprecision(20);
  while (t--) {
    run();
  }
  return 0;
}



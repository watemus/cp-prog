#include <bits/stdc++.h>
using namespace std;
#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second
using ld = long double;
const ld INFLD = 1000000000000000000.0000000;
ld PI = acos(-1);
struct pt {
  long double x, y;
  pt() {}
  pt(long double x, long double y): x(x), y(y) {}
};
pt operator + (pt a, pt b) {
  return pt(a.x + b.x, a.y + b.y);
}
pt operator - (pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}
ld operator * (pt a, pt b) {
  return a.x * b.x + a.y * b.y;
}
ld operator ^ (pt a, pt b) {
  return a.x * b.y - a.y * b.x;
}
pt operator * (long double a, pt b) {
  return pt(a * b.x, a * b.y);
}
ld f1(pt a, pt b) {
  return sqrt((b - a) * (b - a));
}
ld f2(pt a, pt b, pt c) {
  ld ans = INFLD;
  ans = min(ans, f1(a, b));
  ans = min(ans, f1(a, c));
  ld A = c.y - b.y;
  ld B = b.x - c.x;
  ld C = -A * c.x - B * c.y;
  ld h = (A * a.x + B * a.y + C) / sqrt(A * A + B * B);
  pt n(A / sqrt(A * A + B * B), B / sqrt(A * A + B * B));
  pt p1 = a + h * n;
  pt p2 = a - h * n;
  if (abs(A * p1.x + B * p1.y + C) <= 0.000001) {
    if (min(b.x, c.x) <= p1.x && p1.x <= max(b.x, c.x) && min(b.y, c.y) <= p1.y && p1.y <= max(b.y, c.y)) {
      ans = min(ans, abs(h));
    }
  }
  if (abs(A * p2.x + B * p2.y + C) <= 0.000001) {
    if (min(b.x, c.x) <= p2.x && p2.x <= max(b.x, c.x) && min(b.y, c.y) <= p2.y && p2.y <= max(b.y, c.y)) {
      ans = min(ans, abs(h));
    }
  }
  return ans;
}
bool check(pt a, pt b, pt c) {
  if (b.x <= c.x && b.y <= c.y) {
    return (b.x <= a.x && b.y <= a.y);
  }
  if (b.x <= c.x && b.y >= c.y) {
    return (b.x <= a.x && b.y >= a.y);
  }
  if (b.x >= c.x && b.y <= c.y) {
    return (b.x >= a.x && b.y <= a.y);
  }
  return (b.x >= a.x && b.y >= a.y);
}
ld f3(pt a, pt b, pt c) {
  ld ans = INFLD;
  ans = min(ans, f1(a, b));
  ans = min(ans, f1(a, c));
  ld A = c.y - b.y;
  ld B = b.x - c.x;
  ld C = -A * c.x - B * c.y;
  ld h = (A * a.x + B * a.y + C) / sqrt(A * A + B * B);
  pt n(A / sqrt(A * A + B * B), B / sqrt(A * A + B * B));
  pt p1 = a + h * n;
  pt p2 = a - h * n;
  if (abs(A * p1.x + B * p1.y + C) <= 0.000001 && check(p1, b, c)) ans = min(ans, abs(h));
  if (abs(A * p2.x + B * p2.y + C) <= 0.000001 && check(p2, b, c)) ans = min(ans, abs(h));
  return ans;
}
ld f4(pt a, pt b, pt c) {
  ld ans = INFLD;
  ans = min(ans, f1(a, b));
  ans = min(ans, f1(a, c));
  ld A = c.y - b.y;
  ld B = b.x - c.x;
  ld C = -A * c.x - B * c.y;
  ld h = (A * a.x + B * a.y + C) / sqrt(A * A + B * B);
  ans = min(ans, abs(h));
  return ans;
}
bool check2(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 != B2 * C1) return false;
    bool good = true;
    good = good & max(min(c.x, d.x), min(a.x, b.x)) <= min(max(c.x, d.x), max(a.x, b.x));
    return good & max(min(c.y, d.y), min(a.y, b.y)) <= min(max(c.y, d.y), max(a.y, b.y));
  }
  ld x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
  ld y = (C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);
  bool good = true;
  good = good & min(a.x, b.x) <= x && x <= max(a.x, b.x) && min(a.y, b.y) <= y && y <= max(a.y, b.y);
  good = good & min(c.x, d.x) <= x && x <= max(c.x, d.x) && min(c.y, d.y) <= y && y <= max(c.y, d.y);
  return good;
}
ld f6(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f2(a, c, d));
  ans = min(ans, f2(b, c, d));
  ans = min(ans, f2(c, a, b));
  ans = min(ans, f2(d, a, b));
  if (check2(a, b, c, d)) return 0.0000;
  return ans;
}
bool check3(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 == B2 * C1) {
      if (B1 == 0.0000) return !(A1 * C2 != A2 * C1);
      return (check(a, c, d) || check(b, c, d));
    }
    return false;
  }
  ld x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
  ld y = (C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);
  bool good = true;
  good = good & check(pt(x, y), c, d);

  good = good & (min(a.x, b.x) <= x && x <= max(a.x, b.x) && min(a.y, b.y) <= y && y <= max(a.y, b.y));
  return good;
}
ld f7(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f3(a, c, d));
  ans = min(ans, f3(b, c, d));
  ans = min(ans, f2(c, a, b));
  if (check3(a, b, c, d)) return 0.0000;
  return ans;
}
bool check4(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 == B2 * C1) {
      if (B1 == 0.0000) return !(A1 * C2 != A2 * C1);
      return false;
    }
    return false;
  }
  ld x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
  ld y = (C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);
  return min(a.x, b.x) <= x && x <= max(a.x, b.x) && min(a.y, b.y) <= y && y <= max(a.y, b.y);
}
ld f8(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f4(a, c, d));
  ans = min(ans, f4(b, c, d));
  if (check4(a, b, c, d)) return 0.000000;
  return ans;
}
bool check5(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 == B2 * C1) {
      if (B1 == 0.0000) return !(A1 * C2 != A2 * C1);
      return check(a, c, d) || check(b, c, d) || check(c, a, b) || check(d, a, b);
    }
    return false;
  }
  ld x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
  ld y = (C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);
  bool good = true;
  good = good & check(pt(x, y), a, b);
  good = good & check(pt(x, y), c, d);
  return good;
}
ld f11(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f3(a, c, d));
  ans = min(ans, f3(b, c, d));
  ans = min(ans, f3(c, a, b));
  ans = min(ans, f3(d, a, b));
  if (check5(a, b, c, d)) return 0.00000;
  return ans;
}
bool check6(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 == B2 * C1) {
      if (B1 == 0.0000) return !(A1 * C2 != A2 * C1);
      return true;
    }
    return false;
  }
  ld x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
  ld y = (C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);
  return check(pt(x, y), a, b);
}
ld f12(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f4(a, c, d));
  ans = min(ans, f4(b, c, d));
  if (check6(a, b, c, d)) return 0.00000;
  return ans;
}
bool check7(pt a, pt b, pt c, pt d) {
  ld A1, B1, C1, A2, B2, C2;
  A1 = b.y - a.y;
  B1 = a.x - b.x;
  C1 = -A1 * a.x - B1 * a.y;
  A2 = d.y - c.y;
  B2 = c.x - d.x;
  C2 = -A2 * c.x - B2 * c.y;
  if (A1 * B2 == A2 * B1) {
    if (B1 * C2 == B2 * C1) {
      if (B1 == 0.0000) return !(A1 * C2 != A2 * C1);
      return true;
    }
    return false;
  }
  return true;
}
ld f16(pt a, pt b, pt c, pt d) {
  ld ans = INFLD;
  ans = min(ans, f4(a, c, d));
  ans = min(ans, f4(b, c, d));
  if (check7(a, b, c, d)) return 0.0000;
  return ans;
}
signed main() {
  pt a, b, c, d;
  cin >> a.x >> a.y;
  cin >> b.x >> b.y;
  cin >> c.x >> c.y;
  cin >> d.x >> d.y;
  cout << fixed << setprecision(6);
  cout << f1(a, c) << "\n";
  cout << f2(a, c, d) << "\n";
  cout << f3(a, c, d) << "\n";
  cout << f4(a, c, d) << "\n";
  cout << f2(c, a, b) << "\n";
  cout << f6(a, b, c, d) << "\n";
  cout << f7(a, b, c, d) << "\n";
  cout << f8(a, b, c, d) << "\n";
  cout << f3(c, a, b) << "\n";
  cout << f7(c, d, a, b) << "\n";
  cout << f11(a, b, c, d) << "\n";
  cout << f12(a, b, c, d) << "\n";
  cout << f4(c, a, b) << "\n";
  cout << f8(c, d, a, b) << "\n";
  cout << f12(c, d, a, b) << "\n";
  cout << f16(a, b, c, d) << "\n";
  return 0;
}


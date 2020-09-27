//
// Created by watemus on 01.09.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define int long long

int egcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = egcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return d;
}

int gcd(int a, int b) {
  if (b == 0)return a;
  return gcd(b, a % b);
}

optional<pair<int, int>> diofant(int a, int b, int c) {
  int x, y;
  int d = egcd(a, b, x, y);
  if (c % d) {
    //cout << "Impossible";
    return {};
  }
  x *= (c / d);
  y *= (c / d);
  if (x < 0) {
    int k = (abs(x) / (b / d));
    x += k * (b / d);
    y -= k * (a / d);
    if (x < 0) {
      x += (b / d);
      y -= (a / d);
    }
  } else {
    int k = (x / (b / d));
    x -= k * (b / d);
    y += k * (a / d);
  }
  return {{x, y}};
}

void run() {
  int a, b, n, m;
  cin >> a >> b >> n >> m;
  optional<pair<int, int>> pr;
  if (b > a) {
    pr = diofant(n, -m, b - a);
  } else {
    pr = diofant(-n, m, a - b);
  }
  if (pr.has_value()) {
    int x = a + n * pr->first;
    int st = n * m;
    if (x < 0) {
      x += (abs(x) / st) * st;
      if (x < 0)
        x += st;
    }
    if (x > st) {
      x %= st;
    }
    cout << "YES " << x << ' ' << st << '\n';
  } else {
    cout << "NO\n";
  }
}

signed main() {
  int t;
  cin >> t;
  while (t--) run();
  return 0;
}
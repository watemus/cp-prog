#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = rnd() % 100 + 1;
  int m = n - 1 + rnd() % (1000 - n + 1);
  cout << n << ' ' << m << endl;
  const int MX = 1e5;
  for (int i = 1; i < n; i++) {
    int u = i;
    int v = rnd() % i;
    cout << v + 1 << ' ' << u + 1 << ' ' << rnd() % MX + 1 << ' ' << rnd() % MX + 1 << endl;
  }
  for (int i = 0; i < m - n + 1; i++) {
    int u = rnd() % n;
    int v = rnd() % n;
    while (u == v) {
      v = rnd() % n;
    }
    cout << u + 1 << ' ' << v + 1 << ' ' << rnd() % MX + 1 << ' ' << rnd() % MX + 1 << endl;
  }
  return 0;
}
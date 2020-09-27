//
// Created by watemus on 23.08.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  std::mt19937 rnd(atoi(argv[1]));
  //freopen("input.txt", "w", stdout);
  int n, m, d, q;
  n = m = d = q = 5;
  q = 1;
  cout << n << ' ' << m - 1 << ' ' << d << ' ' << q << endl;
  for (int i = 2; i <= n; i++) {
    int v = i;
    int u = (rnd() % (i - 1) + i - 1) % (i - 1) + 1;
    cout << u << ' ' << v << ' ' << (rnd() % d + 100) % d + 10 << endl;
  }
  for (int i = 0; i < n; i++) {
    cout << rnd() % 2 + 1 <<  ' ';
  }
  cout << endl;
  for (int i = 0; i < q; i++) {
    cout << i + 1 << ' ' << rnd() % 2 + 1 << endl;
  }
  return 0;
}
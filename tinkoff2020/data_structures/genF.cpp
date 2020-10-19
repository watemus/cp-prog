//
// Created by watemus on 09.10.2020.
//

//
// Created by watemus on 05.10.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 4, m = 4;
  cout << n << ' ' << m << endl;
  for (int i = 0; i < m / 2; i++) {
    int l = rnd() % n;
    int r = rnd() % n;
    if (l > r) swap(l, r);
    int x = rnd() % 6;
    cout << "^ " << l + 1 << ' ' << r + 1 << ' ' << x << '\n';
  }
  for (int i = 0; i < (m + 1) / 2; i++) {
    int l = rnd() % n;
    int r = rnd() % n;
    if (r < l) swap(l, r);
    cout << "? " << l + 1 << ' ' << r + 1 << '\n';
  }
  cout << "0 0\n";
  return 0;
}

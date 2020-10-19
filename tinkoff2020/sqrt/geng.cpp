//
// Created by watemus on 11.10.2020.
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
  int n = 10;
  int q = 5;
  cout << n << ' ' << q << endl;
  for (int i = 0; i < n; i++) {
    cout << rnd() % 3 << ' ';
  }
  for (int i = 0; i < q; i++) {
    if (rnd() % 2) {
      int p = rnd() % n + 1;
      cout << "2 " << p << ' ' << rnd() % 3 << '\n';
    } else {
      int l = rnd() % n;
      int r = rnd() % n;
      if (r < l) swap(r, l);
      cout << "1 " << l + 1 << ' ' << r + 1 << '\n';
    }
  }
  return 0;
}
